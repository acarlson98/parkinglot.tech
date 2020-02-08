#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();
#include <WiFi.h>
String apiKey = "1YDN2CV3JW7I0IHE";                  //  Enter your Write API key from ThingSpeak
const char *ssid =  "PKI";                                    // replace with your wifi ssid and wpa2 key
const char *pass =  "asdfghjkl"12;
const char* server = "api.thingspeak.com";
WiFiClient client;

//Read Spot info from AVR
int slot1 = 6;
int slot2 = 9;
int slot3 = 15;

void setup() 
{
    Serial.begin(115200);
    delay(10);
    Serial.println("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");

    pinMode(slot1, INPUT);
    pinMode(slot2, INPUT);
    pinMode(slot3, INPUT);
}
void loop() 
{
 if (client.connect(server,80))                                 //   "184.106.153.149" or api.thingspeak.com
    {  
                            
    String postStr = apiKey;
    postStr +="&field1=";
    postStr += String(digitalRead(slot1));
    postStr += "&field2=";
    postStr += String(digitalRead(slot2));
    postStr += "&field3=";
    postStr += String(digitalRead(slot3));
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);                     
    Serial.println("%. Send to Thingspeak.");
    Serial.println("Slot1");
    Serial.print(slot1);
    Serial.println("Slot2");
    Serial.print(slot2);
    Serial.println("Slot3");
    Serial.print(slot3);
    
}
    client.stop();
    Serial.println("Waiting...");
    delay(10000);
}
