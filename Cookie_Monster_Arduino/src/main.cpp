#include <Arduino.h>
#include "MotorControl.h"
#include "LineFollower.h"
#include "pindefs.h"

#define kP 10
#define kD 5
#define T 10 // [ms]

#define DBNC_TIME 10 // [ms]

LineArray LineSensor;
MotorDriver LeftMotor = MotorDriver(enableA, in1, in2, false);
MotorDriver RightMotor = MotorDriver(enableB, in3, in4, false);
DiffDrive myDrive = DiffDrive(&LeftMotor, &RightMotor);

void controller();

int last_err = 0;
float last_ang_vel;

unsigned long last_tick = 0;
bool active = true;
bool not_pressed = true;
unsigned long last_contact = 0;

void setup() {
	Serial.begin(115200);
	LineSensor.init();
	myDrive.init();

	pinMode(BTN_PIN, INPUT_PULLUP);

	myDrive.setSpeed(0,0);
}

void loop() {
	unsigned long now = millis();

	// Check if button is clicked (with debounce)
	if(!digitalRead(BTN_PIN) && (now - last_contact) > DBNC_TIME && not_pressed) {
		active = !active;
		last_contact = now;

		if(!active) {
			myDrive.setSpeed(0,0);
		}
	}

	if(digitalRead(BTN_PIN) && (now - last_contact) > DBNC_TIME && !not_pressed) {
		last_contact = now;
		not_pressed = true;
	}

	// If its time for a controller tick, run the controller
	if(now - last_tick > T) {
		controller();
	}
}

void controller() {
	int raw = LineSensor.readRaw();
	Serial.print("Raw Sense: ");
	Serial.print(raw, BIN);
	int ang_pos = LineSensor.algoPureSum(raw);
	Serial.print(" Ang pos: ");
	Serial.print(ang_pos);
	int ang_err = 0 - ang_pos;
	Serial.print(" Ang Error: ");
	Serial.print(ang_err);
	float ang_vel = kP * ang_err + kD * (ang_err - last_err);
	Serial.print(" Ang vel: ");
	Serial.println(ang_vel);


	// if were active, write to motors
	if(active) myDrive.setSpeed(70, ang_vel);
}