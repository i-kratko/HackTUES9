#include <Arduino.h>

#include <stdio.h>

 

#define ON 1

#define OFF 0

 

/*

 * Pin Description

 */

int vibration_Sensor = A5;

int LED = 13;

 

/*

 * Programme flow Description

 */

int present_condition = 0;

int previous_condition = 0;

 

/*

 * Pin mode setup

 */

void setup() {

pinMode(vibration_Sensor, INPUT);

pinMode(LED, OUTPUT);

}

 

/*

 * Led blink

 */

void led_blink(void);

 

/*

 * main_loop

 */

 

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
