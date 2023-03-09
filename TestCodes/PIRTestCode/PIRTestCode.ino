#define pirPin 2
int calibrationTime = 5;
long unsigned int lowIn;
long unsigned int pause = 5000;
boolean lockLow = true;
boolean takeLowTime;
int PIRValue = 0;
const int ledPin = 4;

void setup() {
   Serial.begin(9600);
   pinMode(pirPin, INPUT);
   pinMode(ledPin, OUTPUT);
}

void loop() {
   PIRSensor();
}

void PIRSensor() {
   if(digitalRead(pirPin) == HIGH) {
      if(lockLow) {
         PIRValue = 1;
         lockLow = false;
         Serial.println("Motion detected.");
         digitalWrite(ledPin, HIGH);
         delay(50);
      }
      takeLowTime = true;
   }
   if(digitalRead(pirPin) == LOW) {
      if(takeLowTime){
         lowIn = millis();takeLowTime = false;
      }
      if(!lockLow && millis() - lowIn > pause) {
         PIRValue = 0;
         lockLow = true;
         Serial.println("Motion ended.");
         digitalWrite(ledPin, LOW);
         delay(50);
      }
   }
}