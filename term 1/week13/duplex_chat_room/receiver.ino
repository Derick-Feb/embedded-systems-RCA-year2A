#include <SoftwareSerial.h>

// RX, TX pins for the slave Arduino
SoftwareSerial bluetooth(10, 11); // RX, TX

void setup() {
  Serial.begin(9600);          // Optional: for debugging on Serial Monitor
  bluetooth.begin(9600);       // Bluetooth module baud rate
  Serial.println("Slave ready...");
}

void loop() {
  // Check if data is received from master via Bluetooth
  if (bluetooth.available()) {
    String msg = bluetooth.readString(); // Read the incoming message
    Serial.println("Received from master: " + msg);

    // Optional: Send reply back to master
    bluetooth.println("Acknowledged: " + msg);
  }

  // Optional: forward Serial Monitor input to master
  if (Serial.available()) {
    bluetooth.write(Serial.read());
  }
}
