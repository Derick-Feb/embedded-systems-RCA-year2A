from machine import Pin
import dht
import time

sensor = dht.DHT11(Pin(4))  # D2 on NodeMCU
led = Pin(5, Pin.OUT)       # D1

while True:
    try:
        sensor.measure()
        temp = sensor.temperature()
        hum = sensor.humidity()
        print("Temperature:", temp, "°C Humidity:", hum, "%")

        # Blink LED every read
        led.value(1)
        time.sleep(0.2)
        led.value(0)

    except OSError as e:
        print("Sensor read error:", e)

    time.sleep(3)  # wait at least 2-3 sec between readings
