#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

/* 	Low Level Motor Driver Interface Class
*	
*	### Description
* 	Implements functionality for controlling a single motor with PWM connected to one side of an L298N motor driver
*	
*	### Arguments
*	`_en_pin`: Enable pin for motor
*	`_in1_pin`: Input 1 pin for motor
*	`_in2_pin`: Input 2 pin for motor
*	
*	### Usage
*	```
*	MotorDriver myMotor = MotorDriver(1, 2, 3) // Creates motor driver connected to pins 1, 2 and 3
*	```
*/
class MotorDriver{
	public:
		enum class Dir{
			FWD,
			RVS
		};

		MotorDriver(int _en_pin, int _in1, int _in2, bool _reversed);

		void init();
		void setVel(float percentage);
		void setDir(Dir direction);
		void setSpeed(float percentage);

	private:
		int enablePin;
		int inputPin1;
		int inputPin2;

		bool reversed;

		Dir current_dir;

};

class DiffDrive{
	public:
		DiffDrive(MotorDriver* _LeftMotor, MotorDriver* _RightMotor);
		
		void init();
		void setSpeed(float linear_vel, float angular_vel);
		void compute_speeds(float linear_vel, float angular_vel, float* L_vel, float* R_vel);
		void rescale_speeds(float* L_vel, float* R_vel);
		void write_speeds(float L_vel, float R_vel);

	private:
		MotorDriver* LeftMotor;
		MotorDriver* RightMotor;
		
		const int wheelbase_coeff = 1;

};

class Encoder{

	private:

	public:
};

class MotorClosedLoop{
	public:
		enum class ControlMode {
			POSITION,
			VELOCITY
		};

		MotorClosedLoop(int _en_pin, int _in1, int _in2, bool _reversed, ControlMode _mode);

		void init();
		void setTargetPos(float t_pos_rot);
		void setTargetVel(float t_vel_rps);
		void setTargetAccel(float t_accel_rpss);

	private:
		MotorDriver myMotor;
		ControlMode my_mode;
};

#endif