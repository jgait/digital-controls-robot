#include <Arduino.h>
#include "motorHandler.h"

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