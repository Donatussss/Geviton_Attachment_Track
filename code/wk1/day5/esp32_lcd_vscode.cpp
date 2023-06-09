#include <Arduino.h>
#include <LiquidCrystal.h>

int rs = 0, en=4, d4=16, d5=17, d6=5, d7=18;
int i = 0;
String ms_array[] = {"Hello", "Goodbye", "Hello again"};
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
}


void loop()
{
  
  lcd.setCursor(0, 0);
  
  for (int thisChar = 0; thisChar < 10; thisChar++)
  {
    lcd.print(thisChar);
    delay(500);
  }
  
  lcd.setCursor(16, 1);
  lcd.autoscroll();
  
  for (int thisChar = 0; thisChar < 10; thisChar++)
  {
    lcd.print(thisChar);
    delay(500);
  }
  
  lcd.noAutoscroll();
  lcd.clear();
}