#ifndef __LINE_FOLLOWER_HANDLER__
#define __LINE_FOLLOWER_HANDLER__

/*
This file is a work in progress based on the example under PIO Library Example 'AveragingReadBarOnly.ino'.
I have only input the setup and nothing else.
*/




#include <Arduino.h>
#include <sensorbar.h>

#define CBUFFER_SIZE 100

// Uncomment one of the four lines to match your SX1509's address
//  pin selects. SX1509 breakout defaults to [0:0] (0x3E).
const uint8_t SX1509_ADDRESS = 0x3E;  // SX1509 I2C address (00)
//const byte SX1509_ADDRESS = 0x3F;  // SX1509 I2C address (01)
//const byte SX1509_ADDRESS = 0x70;  // SX1509 I2C address (10)
//const byte SX1509_ADDRESS = 0x71;  // SX1509 I2C address (11)

SensorBar mySensorBar(SX1509_ADDRESS);
CircularBuffer positionHistory(CBUFFER_SIZE);

void LineFollowerSetup(){
//For this demo, the IR will only be turned on during reads.
  mySensorBar.setBarStrobe();
  //Other option: Command to run all the time
  //mySensorBar.clearBarStrobe();

  //Default dark on light
  mySensorBar.clearInvertBits();
  //Other option: light line on dark
  //mySensorBar.setInvertBits();
  uint8_t returnStatus = mySensorBar.begin();
  if(returnStatus){
	  Serial.println("The line follower is good to go!");
  }
  else
  {
	  Serial.println("The line follower I2C communication FAILED! :(");
	  while(1);
  }
}

#endif