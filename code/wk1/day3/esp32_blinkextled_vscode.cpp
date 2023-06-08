#include <Arduino.h>

int r_pin = 19;
int g_pin = 18;
int b_pin = 5;

void setup()
{
  // put your setup code here, to run once:
  ledcAttachPin(r_pin, 0);
  ledcAttachPin(g_pin, 1);
  ledcAttachPin(b_pin, 2);
  ledcSetup(0, 5000, 8);
  ledcSetup(1, 5000, 8);
  ledcSetup(2, 5000, 8);
}

void loop()
{
  // put your main code here, to run repeatedly:

  for (int i = 255; i >= 0; i--)
  {
    ledcWrite(0, i);
    ledcWrite(1, 255 - i);
    ledcWrite(2, 128 - i);
    delay(1);
  }

  for (int i = 0; i <= 255; i++)
  {
    ledcWrite(0, i);
    ledcWrite(1, 255 - i);
    ledcWrite(2, 128 - i);
    delay(1);
  }
}