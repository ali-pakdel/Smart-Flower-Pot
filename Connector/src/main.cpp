#include <Arduino.h>
#include <string.h>
#include <LiquidCrystal.h>

LiquidCrystal LCD(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(38400);
  delay(100);
  LCD.begin(20, 4);
}

void loop() {
  if (Serial.available() > 0) {
    Serial.println("Changed");
    LCD.print((char)Serial.read());
  }
  delay(500);
}