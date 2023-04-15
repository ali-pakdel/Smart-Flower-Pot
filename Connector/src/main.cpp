#include <Arduino.h>
#include <string.h>

void setup() {
  Serial.begin(38400);
  delay(100);
}

void loop() {
  if (Serial.available() > 0) {
    Serial.println("Changed");
  }
  delay(500);
}