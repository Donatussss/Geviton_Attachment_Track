#include <Arduino.h>

int pin = 2;

void setup() {
  pinMode(2, OUTPUT);
}

void loop() {
  digitalWrite(pin,HIGH);
  delay(500);
  digitalWrite(pin,LOW);
  delay(500);
}