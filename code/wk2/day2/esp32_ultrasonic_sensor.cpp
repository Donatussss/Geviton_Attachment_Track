#include <Arduino.h>

int trigpin = 32;
int echopin = 33;
long duration, distance;
String msg;

void setup() {
  Serial.begin(115200);
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
}

void loop() {
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);

  duration = pulseIn(echopin, HIGH);
  distance = duration/58.2;

  msg = "Distance " + String(distance) + " cm";
  Serial.println(msg);
  delay(1000);
}
