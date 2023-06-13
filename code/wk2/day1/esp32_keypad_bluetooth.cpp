#include <Arduino.h>
#include <Keypad.h>
#include <BluetoothSerial.h>

// Keypad setup
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

String msg = "";
char x;

// Bluetooth setup
BluetoothSerial SerialBT;

void setup()
{
  Serial.begin(115200);
  SerialBT.begin("ESP32test");
}

void loop()
{  
  x = kpd.getKey();
  if (SerialBT.available()){
    Serial.write(SerialBT.read());
  }
  if (Serial.available()){
    SerialBT.write(Serial.read());
  }
  if (x){
    msg = "";
    msg += x;
    while (x != '*')
    {
      x = kpd.getKey();
      if (x and x != '*')
      {
        msg += x;
      }
    }

    Serial.println(msg);
    SerialBT.println(msg);
  }
}