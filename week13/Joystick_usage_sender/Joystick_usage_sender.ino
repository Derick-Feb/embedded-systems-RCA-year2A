#include <SoftwareSerial.h>
SoftwareSerial bluetooth(10, 11); // RX, TX

const int buttonPin = 9;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  // Button press
  if (buttonState == LOW) {
    Serial.println("Button Pressed!");
    bluetooth.write('1');
    delay(300); // debounce
  }

  delay(1000); // small cooldown
}
