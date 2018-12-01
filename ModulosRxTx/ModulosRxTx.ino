#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <DHT.h>

SoftwareSerial serie_virtual(2,3);  //(Tx,Rx)

int pinLED = 8;
bool statusLed;
String valorAnterior, valorActual;

//Sensor de humedad y temperatura DHT11
int sensor = 13;
int temp, humedad;
DHT dht(sensor, DHT11);

void setup() {
  // put your setup code here, to run once:
  serie_virtual.begin(9600);
  //Serial.begin(9600);
  dht.begin();
  
}

void loop() {
  // put your main code here, to run repeatedly:

  valorActual = "0";
  
  humedad = dht.readHumidity();
  temp = dht.readTemperature();

  
  StaticJsonBuffer<200> jsonBuffer;
  
  JsonObject& root = jsonBuffer.createObject();
  root["temperatura"] = temp;
  root["humedad"] = humedad;

  root.printTo(valorActual);

  delay(30);
  if(!valorActual.equals(valorAnterior))
  {
    root.printTo(serie_virtual);
    //root.printTo(Serial);
    //Serial.print(valorActual);
    //Serial.print(valorAnterior);   
  } 
  
  valorAnterior = valorActual;

  //root["statusLed"] = 0; 
  //root["prueba"] = 15.3; 
  //root.printTo(serie_virtual);

  delay(7000);
  //yield();
}
