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
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define LEDPIN 5;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

char buffer[100];
bool spot1;
bool spot2;
bool spot3;
bool spot4;

//get the parking lot state
char checklot(){
  //Put morgans code here

  //convert to json here
    doc["Spot 1"] = spot1;
    doc["Spot 2"] = spot2;
    doc["Spot 3"] = spot3;
    doc["Spot 4"] = spot4;
    serializeJson(doc, buffer);
    
   //display on the OLED
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    // Display static text
    display.print("1: ");
    display.println(spot1);
    display.print("2: ");
    display.println(spot2);
    display.print("3: ");
    display.println(spot3);
    display.print("4: ");
    display.println(spot4);
    display.display(); 
    delay(2000);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LEDDPIN, OUTPUT);
  setupCloudIoT();

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println("Parkinglot.tech");
  display.display(); 
  delay(2000);
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
    
    //publishTelemetry(mqttClient, "/sensors", getDefaultSensor());
    publishTelemetry( buffer);
  }
}
