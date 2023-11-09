#include <Arduino.h>
#include "MotorHandler.h"
#include "LineFollowerHandler.h"

void setup() {
	Serial.begin(115200);
	motorSetup();
	LineFollowerSetup();
}

void loop() {
	// This function breaks the battery, so it's commented out for now.
	// directionControl();
	// delay(1000);

	// speedControl();
	// delay(1000);
	BarReading();
}