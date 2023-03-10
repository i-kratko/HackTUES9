//servo setup
#include <Servo.h>
Servo servo;
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

//counter
int counter = 0;
//communication
int soloMode = 0;
int sendKA = 5;

char KAMsg = 'a';

int waitTillSlaveDead = 10000;

//btn
int lastState = LOW; // the previous state from the input pin
int currentState;

void setup() {
   Serial.begin(9600); // Starting Serial Terminal
   pinMode(ledPin, OUTPUT);
   pinMode(12, INPUT_PULLUP);
   servo.attach(11); //trust
   servo.write(0);
}

void loop() {
  int buttonState = digitalRead(12);
  currentState = digitalRead(12);

  //if(lastState == HIGH && currentState == LOW) {
    //counter++;
    //Serial.println("BTN");
  //}

  // save the last state
  lastState = currentState;
  //sensors
   ultraSonic(pingPin1, echoPin1);
   ultraSonic(pingPin2, echoPin2);
   temperature();
   //protocol
   if (waitTillSlaveDead != 0 && soloMode == 0) {
     if(sendKA == 0) {
      //Serial.println("Sent KA");
      Serial.write(KAMsg);
      Serial.println();
     sendKA = 5;
    }
    else {
     sendKA--;
     }
   }
   
  while(Serial.available() > 0 && waitTillSlaveDead > 0) {
    if (Serial.read() == 'b') {
      waitTillSlaveDead = 10000;
      Serial.println("got msg");
    }
    else if (Serial.read() == 's') {
      counter++;
      Serial.println(counter);
    }
  }

   if (waitTillSlaveDead <= 0) {
     soloMode = 1;
     Serial.println("Slave dead (men im dead)");
   }

   //Serial.println(sendKA);
   waitTillSlaveDead--;
   Serial.println(counter);
   if (counter > 3) {
    servo.write(90);
  }

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
    counter++;
    Serial.println("US DETECT");
    delay(1000);
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