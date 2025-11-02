#include <SoftwareSerial.h>
SoftwareSerial bt(10, 11); // RX = 10, TX = 11

void setup() {
  Serial.begin(38400);
  bt.begin(38400);
  
  Serial.print("BT connected..");
}

void loop() {
  if(Serial.available()){
    bt.write(Serial.read());
  }

  if(bt.available()){
    Serial.print(bt.readString());
  }
}
