//setup for temperature sensor
#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT;
#define DHT11_PIN 10
int tempTimer = 4;
//Ultrasonic sensor #1
const int pingPin1 = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin1 = 6; // Echo Pin of Ultrasonic Sensor
//Ultrasonic sensor #2
const int pingPin2 = 8; // Trigger Pin of Ultrasonic Sensor
const int echoPin2 = 9; // Echo Pin of Ultrasonic Sensor
const int ledPin = 13;
long duration, cm;

//communication
int soloMode = 0;
int sendKA = 5;

char KAMsg = 'a';

int waitTillSlaveDead = 20;

void setup() {
   Serial.begin(9600); // Starting Serial Terminal
   pinMode(ledPin, OUTPUT);
}

void loop() {
   ultraSonic(pingPin1, echoPin1);
   ultraSonic(pingPin2, echoPin2);
   temperature();
   //protocol
   if(sendKA == 0) {
     Serial.println("Sent KA");
     Serial.write(KAMsg);
     Serial.println();
     sendKA = 5;
   }
   else {
     sendKA--;
   }
   //Serial.println(sendKA);
   waitTillSlaveDead--;

}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

void ultraSonic(int pingPin, int echoPin) {
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   cm = microsecondsToCentimeters(duration);
   //Serial.print(cm);
   //Serial.print("cm");
   //Serial.println();

  if(cm <= 5) {
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin, LOW);
  }

   delay(100);
}

void temperature() {
  if(tempTimer == 0) {
    DHT.read(DHT11_PIN);
    //Serial.print("temp:");
    //Serial.print(DHT.temperature);
    //Serial.println();
    tempTimer = 4;
  }
  else {
    tempTimer --;
  }
  
}