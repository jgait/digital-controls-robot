#ifndef __LINEFOLLOWER_HANDLER__
#define __LINEFOLLOWER_HANDLER__

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




class LineFollowerHandler{

  private:
    SensorBar mySensorBar = SensorBar(SX1509_ADDRESS);
    CircularBuffer positionHistory = CircularBuffer(CBUFFER_SIZE);

  public:
    void init();
    void barReading();    
};


// void LineFollowerSetup(){
//   //For this demo, the IR will only be turned on during reads.
//   mySensorBar.setBarStrobe();
//   //Other option: Command to run all the time
//   //mySensorBar.clearBarStrobe();

//   //Default dark on light
//   mySensorBar.clearInvertBits();
//   //Other option: light line on dark
//   //mySensorBar.setInvertBits();
//   uint8_t returnStatus = mySensorBar.begin();
//   if(returnStatus){
// 	  Serial.println("The line follower is good to go!");
//   }
//   else
//   {
// 	  Serial.println("The line follower I2C communication FAILED! :(");
// 	  while(1);
//   }
// }

// void BarReading(){
//   //Wait 50 ms
//   delay(25);


//   //Get the data from the bar and save it to the circular buffer positionHistory.
//   int temp = mySensorBar.getDensity();
//   if( (temp < 4)&&(temp > 0) )
//   {
//     positionHistory.pushElement( mySensorBar.getPosition());
//   }


//   //print me a meter!
//   {
//     int16_t i;
// 	//Get an average of the last 'n' readings
//     int16_t avePos = positionHistory.averageLast( 10 );
//     Serial.print("Scale = 5/char :");
//     for( i = -130; i <= 130; i = i + 5 )
//     {
//       if( i < 0 )
//       {
//         //if avePos within 5 of i
//         if((avePos > (i - 3)) && (avePos <= (i + 2)))
//         {
//           Serial.print("*");
//         }
//         else
//         {
//           Serial.print("-");
//         }
//       }
//       else if( i == 0 )
//       {
//         //if avePos within 5 of i
//         if((avePos > (i - 3)) && (avePos <= (i + 2)))
//         {
//           Serial.print("*");
//         }
//         else
//         {
//           Serial.print("+");
//         }
//       }
//       else if( i > 0 )
//       {
//         //if avePos within 5 of i
//         if((avePos > (i - 3)) && (avePos <= (i + 2)))
//         {
//           Serial.print("*");
//         }
//         else
//         {
//           Serial.print("-");
//         }
//       }
//     }
//     Serial.print(" avePos = ");
//     Serial.println(avePos);
//   }
// }

#endif