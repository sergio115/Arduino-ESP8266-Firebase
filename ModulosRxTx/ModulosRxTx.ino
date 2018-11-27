#include <ArduinoJson.h>
#include <SoftwareSerial.h>

SoftwareSerial serie_virtual(2,3);  //(Tx,Rx)

int pinLED = 8;
bool statusLed;

void setup() {
  // put your setup code here, to run once:
  serie_virtual.begin(9600);
   //Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  const size_t bufferSize = JSON_OBJECT_SIZE(2);
  DynamicJsonBuffer jsonBuffer(bufferSize);
  
  JsonObject& root = jsonBuffer.createObject();
  root["statusLed"] = true;
  root["prueba"] = "Hola";
  
  root.printTo(serie_virtual);
}
