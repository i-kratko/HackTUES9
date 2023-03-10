#include <Arduino.h>
#include <stdio.h>

#define ON 1
#define OFF 0
#define pirPin 2
#define sensor 3
#define LED 4
#define laser 5

int vibration_Sensor = A5;
int calibrationTime = 5;
long unsigned int lowIn;
long unsigned int pause = 5000;
boolean lockLow = true;
boolean takeLowTime;
int PIRValue = 0;
int present_condition = 0;
int previous_condition = 0;

//counter 
int counter = 0;

//communication
int soloMode = 0;
int sendKA = 5;

char KAMsg = 'b';

int waitTillMasterDead = 10000;

void setup() {
   Serial.begin(9600);
   pinMode(pirPin, INPUT);
   pinMode(LED, OUTPUT);
   pinMode(sensor, INPUT);
   pinMode(laser, OUTPUT);
   digitalWrite(laser, HIGH);
}

void loop() {
   //Serial.println(counter);
   PIRSensor();
   bool value = digitalRead(sensor);
    if (value == 0) 
    {
      counter++;
      Serial.println("laserdetect");
      delay(1000);
    }
   
   previous_condition = present_condition;
   present_condition = digitalRead(vibration_Sensor);
   if (previous_condition != present_condition) 
    {
      counter ++;
      Serial.write('s');
      delay(1000);
    }
    if (counter >= 10) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
    
  }

  while(Serial.available() > 0 && waitTillMasterDead > 0) {
    if (Serial.read() == 'a') {
      waitTillMasterDead = 10000;
      Serial.println("got msg");
    }
  }
  
  if(sendKA == 0) {
      //Serial.println("Sent KA");
      Serial.write(KAMsg);
      Serial.println();
     sendKA = 5;
    }
    else {
     sendKA--;
     }

  //if (waitTillMasterDead == 0) {
    //soloMode = 1;
   // Serial.println("SOLO");
  //}

  //waitTillMasterDead--;
  delay(1000);
  //Serial.write('a');
}

void PIRSensor() {
   if(digitalRead(pirPin) == HIGH) {
      if(lockLow) {
         PIRValue = 1;
         lockLow = false;
         counter ++;
         Serial.write('s');
         Serial.println("PIRDETECT");
         delay(100);
      }
      takeLowTime = true;
   }
   if(digitalRead(pirPin) == LOW) {
      if(takeLowTime){
         lowIn = millis();
         takeLowTime = false;
      }
      if(!lockLow && millis() - lowIn > pause) {
         PIRValue = 0;
         lockLow = true;
         delay(50);
      }
   }
   
}
