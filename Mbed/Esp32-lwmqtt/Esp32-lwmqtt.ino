/******************************************************************************
 * Copyright 2018 Google
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/
#include "esp32-mqtt.h"
#include <Wire.h>
#include <ArduinoJson.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define LEDPIN 5;



//sensor defines
#include <NewPing.h>
#define RESULT       5
#define TRIGGER_1    8
#define ECHO_1       9
#define TRIGGER_2    12
#define ECHO_2       13
#define MAX_DISTANCE 400
#define TIMECHECK    5UL
#define TIMELIMIT    60000UL
NewPing sonar(TRIGGER_1, ECHO_1, MAX_DISTANCE);
float duration, distance;
int iterations = 10;
byte lastState, thisState;
unsigned long startMillis, bigMillis;


char buffer[100];
bool spot1;
bool spot2;
bool spot3;
bool spot4;

//get the parking lot state
char checklot(){
  //Put morgans code here
    while(millis() - bigMillis <= TIMELIMIT)
    {
      duration = sonar.ping_median(iterations);
    
      //Determine distance from duration
      // Speed of sound = 343 m/s
      
      distance = (duration / 2) * 0.0343;
      
      //Send results to Serial Monitor
      Serial.print("Morgan Galagher. ECEN 1940  Distance = ");
      if (distance <= 75)
      {
        thisState = HIGH;
      }
      else
      {
        thisState = LOW;
      }
      
      if (lastState != thisState)
      {
      //update to the new state
      lastState = thisState;
      //record time
      startMillis = millis();
      }
      else
      {
        digitalWrite(RESULT, LOW);
      }
      
      if ((lastState == HIGH) && (millis() - startMillis >= TIMECHECK))
      {
      digitalWrite(RESULT, HIGH);
      }
    }
    
    bigMillis = millis();


}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //pinMode(LEDDPIN, OUTPUT);
  setupCloudIoT();

  pinMode(RESULT, OUTPUT);
    
  digitalWrite(RESULT, LOW);
  thisState = LOW;
  bigMillis = 0;
}

unsigned long lastMillis = 0;
void loop() {
  mqtt->loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!mqttClient->connected()) {
    connect();
  }

  // TODO: replace with your code
  // publish a message roughly every second.
  if (millis() - lastMillis > 60000) {
    Serial.println("Publishing value");
    lastMillis = millis();
    checklot();
      //convert to json here
    StaticJsonDocument<100> doc;
    doc["Spot 1"] = spot1;
    doc["Spot 2"] = spot2;
    doc["Spot 3"] = spot3;
    doc["Spot 4"] = spot4;
    serializeJson(doc, buffer);
    
    
    //publishTelemetry(mqttClient, "/sensors", getDefaultSensor());
    publishTelemetry( buffer);
  }
}
