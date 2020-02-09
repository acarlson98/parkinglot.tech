//Parkinglot.tech Thing Speak code
//PKI-IEEE
//Takumi Ito
//2/9/2020

#include "ThingSpeak.h" //install library for thing speak
#include "secrets.h"
#include <WiFi.h>

char ssid[] = "PKI";        // your network SSID (name) 
char pass[] = "12345678";   // your network password
int keyIndex = 0;           // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = 985815;
const char * myWriteAPIKey = "77PYOKK03FXL15CW";

// Initialize our values
String myStatus = "";

// Input ports from AVR
int lot1port = 5;
int lot2port = 18;
int lot3port = 23;
// Input state from AVR
int lot1 = 0;
int lot2 = 0;
int lot3 = 0;


void setup() {
  Serial.begin(115200);  //Initialize serial

  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak

  pinMode(lot1port, INPUT);
  pinMode(lot2port, INPUT);
  pinMode(lot3port, INPUT);
}

void loop() {

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }

  lot1 = digitalRead(lot1port);
  lot2 = digitalRead(lot2port);
  lot3 = digitalRead(lot3port);
  // set the fields with the values
  ThingSpeak.setField(1, lot1);
  ThingSpeak.setField(2, lot2);
  ThingSpeak.setField(3, lot3);
  Serial.println(lot1);
  Serial.println(lot2);
  Serial.println(lot3);
  
  // set the status
  ThingSpeak.setStatus(myStatus);
  
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
 
  delay(20000); // Wait 20 seconds to update the channel again
}
