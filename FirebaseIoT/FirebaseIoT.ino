#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>

// Set these to run example.
#define FIREBASE_HOST "arduino-esp8266-iot.firebaseio.com"  // https://arduino-esp8266-iot.firebaseio.com/
#define FIREBASE_AUTH "pBPtIFktSZMHQhJABOPCcEL4rhvm9u490zstLCNb"
#define WIFI_SSID "c6a88a"
#define WIFI_PASSWORD "280642427"

void setup() {
  Serial.begin(9600);
  
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
  // declare buffer Json 
  StaticJsonBuffer<200> jsonBuffer;

  
void loop() {    
  JsonObject& root = jsonBuffer.parseObject(Serial);
  //JsonObject& root = jsonBuffer.parse(Serial.read());
  bool led = root["statusLed"];
  String cadena = root["prueba"];

  //root.printTo(Serial);
  Serial.println(cadena);
  Serial.println("Prueba");

  Firebase.setBool("statusLed", led);
  Firebase.setString("prueba", cadena);
  delay(1000);
}
