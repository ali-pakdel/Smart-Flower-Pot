#include <Arduino.h>
#include <Wire.h>

using namespace std;

#define Addr 0x40

float oldHum;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  delay(100);
}

void loop()
{
  analogWrite()
  unsigned int data[2];
  float currTemp, currHum;
  Wire.beginTransmission(Addr);
  Wire.write(0xF5);
  Wire.endTransmission();
  delay(50);
  Wire.requestFrom(Addr, 2);
  if (Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }
  currHum = ((data[0] * 256 + data[1]) * 125.0 / 65536.0) - 6;
  Wire.beginTransmission(Addr);
  Wire.write(0xF3);
  Wire.endTransmission();
  delay(50);
  Wire.requestFrom(Addr, 2);
  if (Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }
  currTemp = ((data[0] * 256 + data[1]) * 175.72 / 65536.0) - 46.85;

  if (fabs(currHum - oldHum) > 5)
  {
    oldHum = currHum;
    Serial.print(currHum);
    Serial.print(",");
    Serial.print(currTemp);
    Serial.print(",");
  }
  delay(50);
}