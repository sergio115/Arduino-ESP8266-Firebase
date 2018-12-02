#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

// Set these to run example.
#define FIREBASE_HOST "arduino-esp8266-iot.firebaseio.com"  // https://arduino-esp8266-iot.firebaseio.com/
#define FIREBASE_AUTH "pBPtIFktSZMHQhJABOPCcEL4rhvm9u490zstLCNb"
#define WIFI_SSID "c6a88a"
#define WIFI_PASSWORD "280642427"
//#define WIFI_SSID "LSyC-WIFI"
//#define WIFI_PASSWORD "a1a2a3itd"

SoftwareSerial serie_esp(0,2);  //(Tx,Rx)
String intensidadLluvia;

void setup() {
  Serial.begin(9600);
  serie_esp.begin(9600);
  
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 
}

void loop() {
  //const size_t bufferSize = JSON_OBJECT_SIZE(2) + 30;
  //DynamicJsonBuffer jsonBuffer(bufferSize);
  
  StaticJsonBuffer<200> jsonBuffer;
  
  JsonObject& root = jsonBuffer.parseObject(serie_esp);
  
  int temperatura = root["temperatura"];
  int humedad = root["humedad"];
  int luz = root["luz"];
  int lluvia =  root["lluvia"];

  switch(lluvia) 
  { 
    case 1:
      intensidadLluvia = "Debil";
      break;  
    case 2:
      intensidadLluvia = "Moderada"; 
      break; 
    case 3:
      intensidadLluvia = "Fuerte";
      break; 
    default:
      intensidadLluvia = "No hay lluvia";
  }

  //root.printTo(Serial);
  if(root.success())
  {
    Firebase.setInt("temperatura", temperatura);
    Firebase.setInt("humedad", humedad);
    Firebase.setInt("luz", luz);
    Firebase.setString("lluvia", intensidadLluvia);
    
    root.printTo(Serial);
    //Serial.print("succes");
  }/* else {
    Serial.print(".");
  }*/
    //delay(1000);
    yield();

    //Serial.print((char)serie_esp.read());
}
