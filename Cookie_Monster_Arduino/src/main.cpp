#include <Arduino.h>
#include "MotorController.h"
#include "LineFollower.h"



MotorDriver LeftMotor = MotorDriver(enableA, in1, in2);
MotorDriver RightMotor = MotorDriver(enableB, in3, in4);
LineFollower LineSensor;
MotorClosedLoop CookieMonster;



void setup() {
	Serial.begin(115200);
	LeftMotor.init();
	RightMotor.init();
	LineSensor.init();
}



void loop() {

	LeftMotor.speedControl();
	delay(1000);
	RightMotor.speedControl();
	delay(1000);
	// CookieMonster.driveForward();
	// delay(1000);

	// LineSensor.barReading();
}


