int pin = 2;
void setup() {
  // put your setup code here, to run once:
  pinMode(pin, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("ON");
  digitalWrite(pin,HIGH);
  delay(1000);
  Serial.println("OFF");
  digitalWrite(pin,LOW);
  delay(1000);
}
