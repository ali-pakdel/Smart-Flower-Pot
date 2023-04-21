#include <Arduino.h>
#include <LiquidCrystal.h>

#define EN_MOTOR 11

bool spin;

void setup()
{
  spin = false;
  Serial.begin(9600);
  pinMode(EN_MOTOR, OUTPUT);
  delay(100);
}

float getFloat()
{
  float intPart = 0;
  float frac = 0;
  bool fracReached = false;
  int fracLength = 1;
  while (true)
  {
    if (!Serial.available())
      continue;
    
    char temp = (char)Serial.read();
    if (temp == ',')
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
  if (Serial.available() > 0)
  {
    float temp = getFloat();
    int speed = int(temp) * 255 / 100;
    Serial.println(255 - speed);
    if(temp > 0){
      analogWrite(EN_MOTOR, 255 - speed);
      spin = true;
    } else {
      spin = false;
    }
  }
  
}