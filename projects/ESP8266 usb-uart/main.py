from machine import Pin
from time import sleep

# Pin 2 is the built-in LED on most ESP8266 boards
led = Pin(2, Pin.OUT)

while True:
    led.value(not led.value()) # Switch LED on/off
    sleep(5)                 # 1 second delay