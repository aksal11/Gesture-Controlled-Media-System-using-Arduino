#include <SoftwareSerial.h>

// ADXL335 Pins
const int xPin = A0;
const int yPin = A1;
const int zPin = A2;

int xValue, yValue, zValue;
int prevX = 0, prevY = 0, prevZ = 0;

SoftwareSerial bluetooth(10, 11); // RX, TX

const int threshold = 50;

void setup() {
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(zPin, INPUT);

  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop() {
  xValue = analogRead(xPin);
  yValue = analogRead(yPin);
  zValue = analogRead(zPin);

  // Noise filter
  if (abs(xValue - prevX) < threshold &&
      abs(yValue - prevY) < threshold &&
      abs(zValue - prevZ) < threshold) {
    return;
  }

  Serial.print("X: "); Serial.print(xValue);
  Serial.print(" Y: "); Serial.print(yValue);
  Serial.print(" Z: "); Serial.println(zValue);

  // Gesture Mapping
  if (xValue < 300 && yValue > 400) {
    bluetooth.println("PLAY_PAUSE");
  }
  else if (xValue > 700 && yValue < 300) {
    bluetooth.println("NEXT");
  }
  else if (xValue > 700 && yValue > 400) {
    bluetooth.println("VOLUME_UP");
  }
  else if (xValue < 300 && yValue < 300) {
    bluetooth.println("VOLUME_DOWN");
  }

  prevX = xValue;
  prevY = yValue;
  prevZ = zValue;

  delay(200);
}