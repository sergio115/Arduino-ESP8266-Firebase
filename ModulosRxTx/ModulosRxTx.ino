#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <DHT.h>

SoftwareSerial serie_virtual(2,3);  //(Tx,Rx)
String valorAnterior, valorActual;

//Sensor de humedad y temperatura DHT11
int sensorDht = 13;
int temp, humedad;
DHT dht(sensorDht, DHT11);

// Sensor de luz (Fotoresistencia) KY-018
int sensorLuz = 2; // Entrada analogica
int luzAnalog, luz;

// Sensor de lluvia
int sensorLluvia = 0; // Entrada analogica
int datosLluvia, intensidadLluvia;

void setup() {
  serie_virtual.begin(9600);
  //Serial.begin(9600);
  dht.begin();  
}

void loop() {
  valorActual = "0";
  
  humedad = dht.readHumidity();
  temp = dht.readTemperature();
  luzAnalog = analogRead(sensorLuz);
  luz = map(luzAnalog, 1023 ,0, 0 ,100); 
  datosLluvia = analogRead(sensorLluvia);

  if(datosLluvia > 900)
  {
    intensidadLluvia = 0;  //no hay
  } else if(datosLluvia > 600) 
  {
    intensidadLluvia = 1; //debil
  } else if(datosLluvia > 400) 
  {
    intensidadLluvia = 2; //moderada
  } else{
    intensidadLluvia = 3; //fuerte
  }

  StaticJsonBuffer<200> jsonBuffer;
  
  JsonObject& root = jsonBuffer.createObject();
  root["temperatura"] = temp;
  root["humedad"] = humedad;
  root["luz"] = luz;
  root["lluvia"] = intensidadLluvia;

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
