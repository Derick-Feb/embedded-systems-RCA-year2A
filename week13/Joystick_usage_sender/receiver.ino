#include <SoftwareSerial.h>

SoftwareSerial bluetooth(10, 11); // RX, TX

const int ledPin = 13; // Built-in LED

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  bluetooth.begin(9600);
  Serial.println("Slave ready...");
}

void loop() {
  // Check if data received from master
  if (bluetooth.available()) {
    char data = bluetooth.read(); // read one byte

    if (data == '1') {
      Serial.println("Button pressed on master!");
      digitalWrite(ledPin, HIGH);  // turn on LED
      delay(500);                   // LED on for 0.5s
      digitalWrite(ledPin, LOW);   // turn off LED
    }
  }
}
