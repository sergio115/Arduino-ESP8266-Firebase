#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

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
  
  // declare buffer Json 
  StaticJsonBuffer<200> jsonBuffer;
}

void loop() {    
  char json[] =
  {
    "s01": {
      "Sensor": "led",
      "Status": "0"
    },
    "s02": {
      "Sensor": "proximidad",
      "Distancia": 15
    }
  }

  JsonObject& root = jsonBuffer.parseObject(json);

  bool status = root["Status"];
  int distancia = root["Distancia"];

  Firebase.setBool("Status", false);
  status = Firebase.getBool("Status");
  sendStructure((byte*)&led, sizeof(led));
  delay(1000);
  
  Firebase.setBool("EstadoLed", true);
  led.working = Firebase.getBool("EstadoLed");
  sendStructure((byte*)&led, sizeof(led));
  delay(1000);
}
