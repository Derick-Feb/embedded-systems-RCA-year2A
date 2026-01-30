#include <Wire.h>
#include <MPU6050.h>
#include <SoftwareSerial.h>

MPU6050 mpu;
SoftwareSerial BTSerial(10, 11); // RX, TX for HC-05

#define MPU_POWER_PIN A2  // We'll use A2 as the 5V output for MPU6050

void setup() {
  // Power up MPU6050 through A2
  pinMode(MPU_POWER_PIN, OUTPUT);
  digitalWrite(MPU_POWER_PIN, HIGH); // Output 5V (or close to it)

  delay(100); // small delay to let MPU6050 stabilize

  Serial.begin(38400);
  BTSerial.begin(38400);
  Wire.begin();

  Serial.println("Initializing MPU6050...");
  mpu.initialize();

  if (mpu.testConnection()) {
    Serial.println("MPU6050 connected!");
  } else {
    Serial.println("MPU6050 connection failed!");
  }
}

void loop() {
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  // Send as CSV: ax, ay, az
  BTSerial.print(ax);
  Serial.print(ax);

  BTSerial.print(",");
  Serial.print(", ");

  BTSerial.print(ay);
  Serial.print(ay);

  BTSerial.print(", ");
  Serial.print(", ");

  BTSerial.println(az);
  Serial.print(az);

  Serial.println();

  delay(50); // ~20Hz update rate
}
