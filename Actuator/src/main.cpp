#include <Arduino.h>
#include <LiquidCrystal.h>

LiquidCrystal LCD(12, 11, 5, 4, 3, 2);

void setup()
{
  Serial.begin(9600);
  delay(100);
  LCD.begin(20, 4);
}

void loop()
{
  if (Serial.available())
  {
    LCD.print(Serial.read());
  }
  delay(50);
}