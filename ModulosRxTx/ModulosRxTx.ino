#include <ArduinoJson.h>
#include <SoftwareSerial.h>

SoftwareSerial serie_virtual(2,3);  //(Tx,Rx)

int pinLED = 8;
bool statusLed;
String a = "a", b, c;

void setup() {
  // put your setup code here, to run once:
  serie_virtual.begin(9600);
  //Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //const size_t bufferSize = JSON_OBJECT_SIZE(2);
  //DynamicJsonBuffer jsonBuffer(bufferSize);
  
  StaticJsonBuffer<200> jsonBuffer;
  
  JsonObject& root = jsonBuffer.createObject();
  root["statusLed"] = 1;
  root["prueba"] = 10.5;


  root.printTo(serie_virtual);

   
  delay(7000);

  root["statusLed"] = 0;
  root["prueba"] = 15.3;


  root.printTo(serie_virtual);

   
  delay(7000);
  //yield();
}
