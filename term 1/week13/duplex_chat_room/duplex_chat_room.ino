#include <SoftwareSerial.h>
SoftwareSerial bluetooth(10, 11); // RX, TX
void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  delay(2000);  // let BT module connect
  // Send message once on startup
  bluetooth.println("hello slave");
}
void loop() {
  // Optional: forward Serial Monitor input to slave
  if (Serial.available()) {
    bluetooth.write(Serial.read());
  }
  if(bluetooth.available()){
    String ms= bluetooth.readString();
    Serial.println("Received : " + ms);
  }
}