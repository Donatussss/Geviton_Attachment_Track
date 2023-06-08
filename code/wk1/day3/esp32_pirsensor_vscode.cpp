#include <Arduino.h>

int ch0 = 0;
int r_pin = 19;
int pir_out_pin = 18;
long prev_time = millis();
long curr_time = millis();
long timer_limit = 10000;
bool timer_status = false;
int r_value = 0;

void inform();

void setup()
{
  ledcAttachPin(r_pin, ch0);
  ledcSetup(ch0, 5000, 8);
  pinMode(pir_out_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(pir_out_pin), inform, RISING);
  Serial.begin(115200);
}

void loop()
{
  curr_time = millis();

  if (timer_status && (curr_time - prev_time >= timer_limit))
  {
    r_value = 0;
    timer_status = false;
    Serial.println("Motion stopped");
  }

  ledcWrite(ch0, r_value);
}

void inform()
{
  prev_time = millis();
  r_value = 255;
  timer_status = true;
  Serial.println("Motion detected");
}