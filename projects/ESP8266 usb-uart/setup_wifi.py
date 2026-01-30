import network
import webrepl
# This enables the Access Point
ap = network.WLAN(network.AP_IF)
ap.active(True)
ap.config(essid="ESP8266-WIRELESS", password="password123")
# This starts WebREPL
webrepl.start()
print("Wireless Setup Complete")