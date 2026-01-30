# main.py
# ESP8266 + DHT11 Monitoring + LED Control over MQTT
import time
import network
import machine
import ubinascii
import ujson as json
from machine import Pin
import dht
from umqtt.simple import MQTTClient

# ------------------------------------------------------------------
# CONFIGURATION (EDIT THESE VALUES)
# ------------------------------------------------------------------
WIFI_SSID = "RCA"      # Replace with your SSID 
WIFI_PASS = "@RcaNyabihu2023"  # Replace with your Password 

MQTT_HOST = "broker.benax.rw"
MQTT_PORT = 1883

TOPIC_DATA      = b"sensors/dht"
TOPIC_LED_CMD   = b"control/led"
TOPIC_LED_STATE = b"control/led/status"

# Unique Client ID based on hardware MAC address [cite: 173, 241]
CLIENT_ID  = b"esp8266_" + ubinascii.hexlify(machine.unique_id())
TOPIC_STATUS = b"iot/status/" + CLIENT_ID

PUBLISH_INTERVAL_SEC = 5

# Offset to convert MicroPython epoch (2000) to Unix epoch (1970) [cite: 174]
UNIX_OFFSET = 946684800

# ------------------------------------------------------------------
# HARDWARE SETUP [cite: 69, 175]
# ------------------------------------------------------------------
# DHT11 data pin: D1 (GPIO5)
sensor = dht.DHT11(Pin(5))

# LED pin: D2 (GPIO4)
led = Pin(4, Pin.OUT)
led.value(0)  # Ensure LED is OFF at boot [cite: 175]

client = None

# ------------------------------------------------------------------
# NETWORK & TIME FUNCTIONS [cite: 175, 176]
# ------------------------------------------------------------------
def wifi_connect():
    sta = network.WLAN(network.STA_IF)
    sta.active(True)
    if not sta.isconnected():
        print("Connecting to Wi-Fi...")
        sta.connect(WIFI_SSID, WIFI_PASS)
        start = time.ticks_ms()
        while not sta.isconnected():
            # 20-second timeout to prevent infinite hanging [cite: 175]
            if time.ticks_diff(time.ticks_ms(), start) > 20000:
                raise RuntimeError("Wi-Fi connection timeout")
            time.sleep(0.3)
    print("Wi-Fi connected:", sta.ifconfig())

def sync_time():
    try:
        import ntptime
        for _ in range(10):
            try:
                ntptime.settime()
                print("Time synchronized via NTP")
                return True
            except Exception:
                time.sleep(2)
    except ImportError:
        print("ntptime module not available")
    print("NTP synchronization failed")
    return False

def unix_time():
    """Returns standard Unix timestamp."""
    return int(time.time() + UNIX_OFFSET)

# ------------------------------------------------------------------
# MQTT FUNCTIONS [cite: 176, 177]
# ------------------------------------------------------------------
def publish_led_state(c):
    state = b"ON" if led.value() else b"OFF"
    c.publish(TOPIC_LED_STATE, state, retain=True)
    print("Reported LED state:", state.decode())

def mqtt_callback(topic, msg):
    global client
    if topic == TOPIC_LED_CMD:
        command = msg.decode().strip().upper()
        # Support multiple command formats [cite: 214]
        if command in ("ON", "1", "TRUE"):
            led.value(1)
        else:
            led.value(0)
        publish_led_state(client)

def mqtt_connect():
    c = MQTTClient(
        client_id=CLIENT_ID,
        server=MQTT_HOST,
        port=MQTT_PORT,
        keepalive=30
    )
    # Set Last Will to notify others if device drops offline [cite: 113, 177]
    c.set_last_will(TOPIC_STATUS, b"offline", retain=True)
    c.connect()
    c.publish(TOPIC_STATUS, b"online", retain=True)
    print("MQTT connected as:", CLIENT_ID.decode())
    return c

# ------------------------------------------------------------------
# MAIN EXECUTION [cite: 177, 178]
# ------------------------------------------------------------------
try:
    wifi_connect()
    sync_time()
    client = mqtt_connect()
    client.set_callback(mqtt_callback)
    client.subscribe(TOPIC_LED_CMD)
    publish_led_state(client)

    last_publish = time.ticks_ms()

    while True:
        try:
            # Check for incoming MQTT messages [cite: 178]
            client.check_msg()

            # Periodic sensor publication [cite: 178]
            if time.ticks_diff(time.ticks_ms(), last_publish) >= PUBLISH_INTERVAL_SEC * 1000:
                last_publish = time.ticks_ms()
                
                try:
                    sensor.measure()
                    payload = {
                        "temperature": sensor.temperature(),
                        "humidity": sensor.humidity(),
                        "ts": unix_time()  # Include timestamp for dashboard validation [cite: 108, 179]
                    }
                    client.publish(TOPIC_DATA, json.dumps(payload), retain=True)
                    print("Published:", payload)
                except OSError as e:
                    print("DHT11 error:", e)

            time.sleep_ms(40) # Small delay to save power/prevent CPU hogging

        except Exception as e:
            print("Loop error, reconnecting:", e)
            time.sleep(5)
            machine.reset() # Hard reset on critical failure for reliability [cite: 116]

except Exception as e:
    print("Critical Boot Error:", e)
    time.sleep(10)
    machine.reset()