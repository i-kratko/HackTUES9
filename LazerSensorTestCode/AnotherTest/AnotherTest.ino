#define laser 2
#define sensor 3

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(laser, OUTPUT);
  pinMode(sensor, INPUT);
  digitalWrite(laser, HIGH);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  bool value = digitalRead(sensor);
  Serial.print(value);
}
