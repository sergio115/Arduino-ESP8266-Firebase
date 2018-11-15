int pinLED = 8;

struct statusLed 
{
  bool working;
  String miLed; 
};

struct statusLed led;

void recieveStructure(byte *structurePointer, int structureLength)
{
  if(Serial.available() < sizeof(led)) return;
  Serial.readBytes(structurePointer, structureLength);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  recieveStructure((byte*)&led, sizeof(led));
  analogWrite(8, led.working);
  delay(1000);

  digitalWrite(8, 0/*led.working*/);
  delay(1000);

}
