#include <Arduino.h>
#include <Keypad.h>

const byte ROWS = 4; // four rows
const byte COLS = 3; // three columns
char keys[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}};
byte rowPins[ROWS] = {0, 4, 16, 17}; // connect to the row pinouts of the kpd
byte colPins[COLS] = {5, 18, 19};    // connect to the column pinouts of the kpd

Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String msg;
char x;

void setup()
{
  Serial.begin(115200);  
  msg = "";
  Serial.println("Enter your number.\nConclude with *");
}

void loop()
{
  x = char(Serial.read());
  msg = "";
  while (x != '*'){
    x = kpd.getKey();
    if(x and x != '*'){
      msg += x;
    }
  }
  
  Serial.println("Your string is: " + msg);
}