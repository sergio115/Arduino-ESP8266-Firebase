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
  const size_t bufferSize = JSON_OBJECT_SIZE(2) + 30;
  DynamicJsonBuffer jsonBuffer(bufferSize);
  
  
  JsonObject& root = jsonBuffer.parseObject(serie_esp);
  
  bool statusLed = root["statusLed"]; // true
  const char* prueba = root["prueba"]; // "Hola"
    
    Firebase.setBool("statusLed", statusLed);
    Firebase.setString("prueba", prueba);

    root.printTo(Serial);

    //Serial.print((char)serie_esp.read());
}
