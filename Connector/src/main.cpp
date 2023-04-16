#include <Arduino.h>
#include <string.h>
#include <LiquidCrystal.h>

LiquidCrystal LCD(12, 11, 5, 4, 3, 2);

void setup()
{
  Serial.begin(9600);
  delay(100);
  LCD.begin(20, 4);
}

bool readyToClear;

float getFloat()
{
  float intPart = 0;
  float frac = 0;
  bool fracReached = false;
  int fracLength = 1;
  while (Serial.available() > 0)
  {
    char temp = (char)Serial.read();
    if (temp == '.')
    {
      fracReached = true;
    }
    else if (temp == ',')
    {
      return intPart + frac / fracLength;
    }
    else
    {
      int num = (int)temp - (int)'0';
      if (fracReached)
      {
        frac = frac * 10 + num;
        fracLength *= 10;
      }
      else
      {
        intPart = intPart * 10 + num;
      }
    }
  }
  return intPart + frac / fracLength;
}

void loop()
{
  float humidity;
  float temperature;
  if (Serial.available())
  {
    LCD.clear();
    humidity = getFloat();
    temperature = getFloat();
    LCD.println(humidity);
    LCD.print(temperature);
    if (humidity > 30)
    {
      Serial.print(0);
    }
    else if (humidity > 20)
    {
      if (temperature > 25)
        Serial.print(10);
      else
        Serial.print(0);
    }
    else if (humidity > 10)
    {
      Serial.print(20);
    }
    else
    {
      Serial.print(25);
    }
  }
  delay(50);
}