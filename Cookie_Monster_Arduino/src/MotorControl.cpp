#include <Arduino.h>
#include "MotorControl.h"

// ===== Differential Drive Class ====

DiffDrive::DiffDrive(MotorDriver* _LeftMotor, MotorDriver* _RightMotor) : 	LeftMotor(_LeftMotor),
																			RightMotor(_RightMotor)
{}

void DiffDrive::init() {
	LeftMotor->init();
	RightMotor->init();

	LeftMotor->setVel(0);
	RightMotor->setVel(0);
}

void DiffDrive::compute_speeds(float linear_vel, float angular_vel, float* L_vel, float* R_vel) {
	*L_vel = linear_vel - (angular_vel * wheelbase_coeff);
	*R_vel = linear_vel + (angular_vel * wheelbase_coeff);
}

void DiffDrive::rescale_speeds(float* L_vel, float* R_vel) {
	float largest = max(abs(*L_vel), abs(*R_vel));
	//Serial.print(" Largest: ");
	//Serial.print(largest);
	if(largest > 100) {
		float factor = 100 / largest;
		*L_vel = *L_vel * factor;
		*R_vel = *R_vel * factor;
	}
}

void DiffDrive::write_speeds(float L_vel, float R_vel) {
	// Serial.print(" Write_Leftvel: ");
	// Serial.print(L_vel);
	// Serial.print(" Write_Rightvel: ");
	// Serial.print(R_vel);
	LeftMotor->setVel(L_vel);
	RightMotor->setVel(R_vel);
}

void DiffDrive::setSpeed(float linear_vel, float angular_vel) {
	float left_vel = 0;
	float right_vel = 0;

	compute_speeds(linear_vel, angular_vel, &left_vel, &right_vel);
	rescale_speeds(&left_vel, &right_vel);
	write_speeds(left_vel, right_vel);
}


// ===== Motor Driver Class ====

MotorDriver::MotorDriver(int _en_pin, int _in1, int _in2, bool _reversed) :   enablePin(_en_pin), 
                                                                inputPin1(_in1), 
                                                                inputPin2(_in2),
																reversed(_reversed) 
{}


void MotorDriver::init(){
    // Set all the motor control pins to outputs
	pinMode(enablePin, OUTPUT);
	pinMode(inputPin1, OUTPUT);
	pinMode(inputPin2, OUTPUT);

	// Turn off motor - Initial state
	digitalWrite(enablePin, LOW);
}

void MotorDriver::setVel(float percentage){
	if(percentage >= 0) {
		setDir(Dir::FWD);
		setSpeed(abs(percentage));
	}
	else if(percentage < 0) {
		setDir(Dir::RVS);
		setSpeed(abs(percentage));
	}
}


void MotorDriver::setDir(Dir direction){
	// Handle reversed motor
	if(reversed) {
		// Serial.print(" Reversed: ");
		// Serial.print( reversed );
		if(direction == Dir::FWD) { direction = Dir::RVS; }
		else if(direction == Dir::RVS) { direction = Dir::FWD; }
	}

	// Set direction
	if(direction == Dir::FWD){
		//Serial.print(" in1, in2: HIGH, lOW ");
		digitalWrite(inputPin1, HIGH);
		digitalWrite(inputPin2, LOW);
	}
	else{
		//Serial.print(" in1, in2: LOW, HIGH ");
		digitalWrite(inputPin1, LOW);
		digitalWrite(inputPin2, HIGH);
	}
}


void MotorDriver::setSpeed(float percentage){
	int pwm = int(255 * (percentage/100)); 
	analogWrite(enablePin, pwm);
}



MotorClosedLoop::MotorClosedLoop(int _en_pin, int _in1, int _in2, bool _reversed, MotorClosedLoop::ControlMode _mode) : myMotor(_en_pin, _in1, _in2, _reversed), my_mode(_mode)
{}


void MotorClosedLoop::setTargetPos(float t_vel_rot) {

}



void MotorClosedLoop::setTargetVel(float t_vel_rps) {

}



void MotorClosedLoop::setTargetAccel(float t_vel_rpss) {

}