#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT;

#define laser 2
#define sensor 3
#define LED 4
#define DHT11_PIN 10

int counter = 0;

void setup() {
  Serial.begin(9600);
  pinMode(laser, OUTPUT);
  pinMode(sensor, INPUT);
  pinMode(LED, OUTPUT);

  digitalWrite(laser, HIGH);
}

void loop() {
  bool value = digitalRead(sensor);
  DHT.read(DHT11_PIN);
  Serial.print("temp:");
  Serial.print(DHT.temperature);
  Serial.println();
  delay(1000);

  if (value == 0) {
    counter ++;
    delay(1000);
  }
  if (DHT.temperature > 25)
  {
    counter ++;
    delay(1000);
  }
  if (counter >= 2) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
    
  }
  Serial.println(counter);
}
