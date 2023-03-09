#define laser 2
#define sensor 3
#define LED 4

void setup() {
  Serial.begin(9600);
  pinMode(laser, OUTPUT);
  pinMode(sensor, INPUT);
  pinMode(LED, OUTPUT);

  digitalWrite(laser, HIGH);
}

void loop() {
  bool value = digitalRead(sensor);

  if (value == 0) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
}
