#include <SoftwareSerial.h>
SoftwareSerial bluetooth(10, 11); // RX, TX
const int buttonPin = 9;
int pin =7;
void setup() {
 pinMode(buttonPin, INPUT_PULLUP);
 Serial.begin(9600);
 bluetooth.begin(9600);
 pinMode(pin, HIGH);
}
void loop() {
 int buttonState = digitalRead(buttonPin);

 if (buttonState == LOW) {
 Serial.println("Button Pressed!");
 bluetooth.write('1');
 delay(500);
 }
}