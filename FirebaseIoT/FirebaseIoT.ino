//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

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
  
  // use Json 
  StaticJsonBuffer<200> jsonBuffer;
  
  char json[] =
 {
    "s01": {
      "Sensor": "led",
      "Status": "HIGH"
    },
    "s02": {
      "Sensor": "proximidad",
      "Distancia": 15
    },
    "Data":"[HIGH,15]"
  }

  JsonObject& root = jsonBuffer.parseObject(json);

  const char* sensor = root["EstadoLed"];
  bool time = root["time"];
  double latitude = root["data"][0];
  double longitude = root["data"][1];

}

void loop() {
  Firebase.setBool("EstadoLed", false);
  led.working = Firebase.getBool("EstadoLed");
  sendStructure((byte*)&led, sizeof(led));
  delay(1000);
  
  Firebase.setBool("EstadoLed", true);
  led.working = Firebase.getBool("EstadoLed");
  sendStructure((byte*)&led, sizeof(led));
  delay(1000);

  Firebase.setString("message", "LOW");
  led.miLed = Firebase.getString("message");
  sendStructure((byte*)&led, sizeof(led));
  
  Firebase.setString("message", "HIGH");
  led.miLed = Firebase.getString("message");
  sendStructure((byte*)&led, sizeof(led));
}
