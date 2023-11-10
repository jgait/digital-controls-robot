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



void MotorDriver::directionControl(){
    // Set motors to maximum speed
	// For PWM maximum possible values are 0 to 255
	analogWrite(enablePin, 255);

	// Turn on motor A & B
	digitalWrite(inputPin1, HIGH);
	digitalWrite(inputPin2, LOW);
	delay(2000);
	
	// Now change motor directions
	digitalWrite(inputPin1, LOW);
	digitalWrite(inputPin2, HIGH);
	delay(2000);
	
	// Turn off motors
	digitalWrite(inputPin1, LOW);
	digitalWrite(inputPin2, LOW);
}



void MotorDriver::speedControl(){
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


