#include <Arduino.h>
#include "MotorHandler.h"

void setup() {
	Serial.begin(9600);
	motorSetup();
}

void loop() {
	directionControl();
	delay(1000);
	speedControl();
	delay(1000);
}