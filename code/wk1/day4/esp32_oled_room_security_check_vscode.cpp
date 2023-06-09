#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// Led
int ch0 = 0;
int r_pin = 19;
int r_value = 0;

// Pir_sensor
int pir_out_pin = 18;
long prev_time = millis();
long curr_time = millis();
long timer_limit = 10000;
bool timer_status = false;

// Oled screen
Adafruit_SSD1306 display(128, 32, &Wire, -1);

// Function declarations
void inform();

void setup()
{
  // Led
  ledcAttachPin(r_pin, ch0);
  ledcSetup(ch0, 5000, 8);

  // Pir_sensor
  pinMode(pir_out_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(pir_out_pin), inform, RISING);
  Serial.begin(115200);

  // Oled screen
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.display();
}

void loop()
{
  curr_time = millis();

  if (timer_status && (curr_time - prev_time >= timer_limit))
  {
    r_value = 0;
    timer_status = false;
    Serial.println("Motion stopped");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Room secure");
    display.display();
  }

  if (timer_status){
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Jambazi Alert!");
    display.display();
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