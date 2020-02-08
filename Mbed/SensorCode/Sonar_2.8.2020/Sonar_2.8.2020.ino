/*
  Sonar Distance Measurement

  Uses the HC-SR04 Ultrasonic Range Finder to measure distance 
  between the emitter and a solid object using the speed of sound.
  TRIG is wrired to pin 10, and ECHO is wired to pin 13.

  The circuit:
  - UNO Arduino
  - HC-SR04 Ultrasonic Range Finder
  - 10 Wires

  created 8 Feb 2020
  by Morgan Gallagher

  This code is in the public domain.
  
  https://www.youtube.com/watch?v=6F1B_N6LuKw&t=123s
*/

// NewPing - Version: Latest 
#include <NewPing.h>

#define RESULT1      5
#define RESULT2      6
#define RESULT3      7
#define TRIGGER_1    8
#define ECHO_1       9
#define TRIGGER_2    10
#define ECHO_2       11
#define TRIGGER_3    12
#define ECHO_3       13
#define MAX_DISTANCE 400
#define TIMECHECK    5UL
#define TIMELIMIT    60000UL

float duration, distance;
int iterations = 10;

byte lastState, thisState;
unsigned long startMillis, bigMillis;


void setup() {
  
    pinMode(RESULT1, OUTPUT);
    pinMode(RESULT2, OUTPUT);
    pinMode(RESULT3, OUTPUT);
    
    digitalWrite(RESULT1, LOW);
    digitalWrite(RESULT2, LOW);
    digitalWrite(RESULT3, LOW);
    thisState = LOW;
    bigMillis = 0;
}

void loop() {
    
    ////////////////test sensor 1/////////////////
    while(millis() - bigMillis <= TIMELIMIT)
    {
      NewPing sonar(TRIGGER_1, ECHO_1, MAX_DISTANCE);
      
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
        digitalWrite(RESULT1, LOW);
      }
      
      if ((lastState == HIGH) && (millis() - startMillis >= TIMECHECK))
      {
      digitalWrite(RESULT1, HIGH);
      }
    }
    
    bigMillis = millis();
    
    /////////////////
    while(millis() - bigMillis <= TIMELIMIT)
    {
      NewPing sonar(TRIGGER_1, ECHO_1, MAX_DISTANCE);
      
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
        digitalWrite(RESULT1, LOW);
      }
      
      if ((lastState == HIGH) && (millis() - startMillis >= TIMECHECK))
      {
      digitalWrite(RESULT1, HIGH);
      }
    }
    
    bigMillis = millis();
    
}
