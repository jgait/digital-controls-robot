#include <Arduino.h>
#include "MotorHandler.h"
#include "LineFollowerHandler.h"

MotorHandler LeftMotor = MotorHandler(enableA, in1, in2);
MotorHandler RightMotor = MotorHandler(enableB, in3, in4);
LineFollowerHandler LineFollower;

void setup() {
	Serial.begin(115200);
	LeftMotor.init();
	RightMotor.init();
	LineFollower.init();
}

void loop() {
	// This function breaks the battery, so it's commented out for now.
	// directionControl();
	// delay(1000);

	LeftMotor.speedControl();
	delay(1000);
	RightMotor.speedControl();
	delay(1000);
	// LineFollower.barReading();
}