#include <ArduinoJson.h>

int pinLED = 8;
bool statusLed;
  

StaticJsonBuffer<200> jsonBuffer;
JsonObject& root = jsonBuffer.createObject();


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  statusLed = true;
  root["statusLed"] = statusLed;
  root["prueba"] = "Hola";
  delay(1000);
  root.printTo(Serial);
  
  statusLed = false;
  root["statusLed"] = statusLed;
  root["prueba"] = "Adios";
  delay(1000);
  root.printTo(Serial);
}
