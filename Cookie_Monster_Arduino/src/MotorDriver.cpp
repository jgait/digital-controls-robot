#include <Arduino.h>
#include "MotorController.h"



MotorDriver::MotorDriver(int _en_pin, int _in1, int _in2) :   enablePin(_en_pin), 
                                                                inputPin1(_in1), 
                                                                inputPin2(_in2) 
{}



void MotorDriver::init(){
    // Set all the motor control pins to outputs
	pinMode(enablePin, OUTPUT);
	pinMode(inputPin1, OUTPUT);
	pinMode(inputPin2, OUTPUT);

	// Turn off motors - Initial state
	digitalWrite(inputPin1, LOW);
	digitalWrite(inputPin2, LOW);
}


// needs to be adjusted
void MotorDriver::directionControl(int direction){
	// switch directions
	if(direction == 1){
		digitalWrite(inputPin1, HIGH);
		digitalWrite(inputPin2, LOW);
	}
	else{
		digitalWrite(inputPin1, LOW);
		digitalWrite(inputPin2, HIGH);
	}
}


// needs to be adjusted
void MotorDriver::speedControl(float percentage){
    // Turn on motors
	digitalWrite(inputPin1, LOW);
	digitalWrite(inputPin2, HIGH);
	
	// Accelerate from zero to maximum speed
	for (int i = 0; i < 256; i++) {
		analogWrite(enablePin, i);
		delay(20);
	}
	
	// Decelerate from maximum speed to zero
	for (int i = 255; i >= 0; --i) {
		analogWrite(enablePin, i);
		delay(20);
	}
	
	// Now turn off motors
	digitalWrite(inputPin1, LOW);
	digitalWrite(inputPin2, LOW);
}


