#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#define enableA 9
#define in1 8
#define in2 7

#define enableB 3
#define in3 5
#define in4 4



class MotorClosedLoop{

	private:
		MotorDriver myMotor;

	public:
		MotorClosedLoop(int _en_pin, int _in1, int _in2);

		void driveForward();
		void driveBackward();
		void spin();
};



class MotorDriver{

	private:
		int enablePin;
		int inputPin1;
		int inputPin2;

	public:
		MotorDriver(int _en_pin, int _in1, int _in2);

		void init();
		void directionControl();
		void speedControl();
};



class Encoder{

	private:

	public:
};



#endif