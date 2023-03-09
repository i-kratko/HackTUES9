#include <Arduino.h>

#include <stdio.h>
#define ON 1
#define OFF 0

int vibration_Sensor = A5;

int LED = 13;
int present_condition = 0;
int previous_condition = 0;
void setup() {

pinMode(vibration_Sensor, INPUT);
pinMode(LED, OUTPUT);
}

void led_blink(void);
void loop() {

previous_condition = present_condition;
present_condition = digitalRead(A5); // Reading digital data from the A5 Pin of the Arduino.
if (previous_condition != present_condition) {
led_blink();
} else {

digitalWrite(LED, OFF);

}

}

void led_blink(void) {
digitalWrite(LED, ON);
delay(250);
digitalWrite(LED, OFF);
delay(250);
digitalWrite(LED, ON);
delay(250);
digitalWrite(LED, OFF);
delay(250);

}
