#include <Arduino.h>
#include <LiquidCrystal.h>
#include <BluetoothSerial.h>

String temp_string;
int rs = 0, en=4, d4=16, d5=17, d6=5, d7=18;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
BluetoothSerial SerialBT;

void set_lcd(String chat_client);

void setup() {
  lcd.begin(16, 2);
  SerialBT.begin("Esp32_test");
  Serial.begin(115200);
}


void loop()
{
  if (Serial.available()){
    set_lcd("MCU");

    while(Serial.available()){
      lcd.print(char(Serial.read()));
    }
  }

  if (SerialBT.available()){
    set_lcd("External Device");
    while (SerialBT.available())
    {
      lcd.print(char(SerialBT.read()));
    }
  }
  
}

void set_lcd(String chat_client){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.println(chat_client);
  lcd.setCursor(0, 1);
}