#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Stepper.h>

#define MOTOR_SPEED 1200
#define EN_MOTOR 11


Stepper stepper(4, 8, 9, 10, 11);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

bool spin;

void setup()
{
  spin = false;
  Serial.begin(9600);
  pinMode(EN_MOTOR, OUTPUT);
  analogWrite(EN_MOTOR, 255);
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
  if (spin)
    stepper.step(1);
  if (Serial.available() > 0)
  {
    float temp = getFloat();
    int speed = int(temp) * 255 / 100;
    Serial.println(255 - speed);
    if(temp > 0){
      //analogWrite(EN_MOTOR, 255);
      spin = true;
    } else {
      spin = false;
    }
  }
  
}