#ifndef __MOTOR_HANDLER__
#define __MOTOR_HANDLER__

#include <Arduino.h>

#define enableA 9
#define in1 8
#define in2 7

#define enableB 3
#define in3 5
#define in4 4

// goes in header
class MotorHandler{

private:
	int enablePin;
	int inputPin1;
	int inputPin2;

public:
	MotorHandler(int _en_pin, int _in1, int _in2);

	void init();
	void directionControl();
	void speedControl();
};


#endif