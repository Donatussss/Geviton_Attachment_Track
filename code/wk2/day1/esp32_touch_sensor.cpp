#include <Arduino.h>

int pin4 = 4;
int pin2 = 2;
int state = 0;

void setup()
{
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  Serial.println("ESP32 Touch Test");
  pinMode(pin4, INPUT);
  pinMode(pin2, OUTPUT);
}

void loop()
{
  Serial.println(digitalRead(pin4)); // get value using T0
  digitalWrite(pin2, digitalRead(pin4));
  delay(1000);
}
