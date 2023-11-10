#include "LineFollowerHandler.h"
#include <Arduino.h>


void LineFollowerHandler::init(){ 
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

void LineFollowerHandler::barReading(){
    //Wait 50 ms
    delay(25);


    //Get the data from the bar and save it to the circular buffer positionHistory.
    int temp = mySensorBar.getDensity();
    if( (temp < 4)&&(temp > 0) ) {
        positionHistory.pushElement( mySensorBar.getPosition());
    }


    //print me a meter!
    {
    int16_t i;
    //Get an average of the last 'n' readings
    int16_t avePos = positionHistory.averageLast( 10 );
    Serial.print("Scale = 5/char :");
    for( i = -130; i <= 130; i = i + 5 ) {
        if( i < 0 ) {
            //if avePos within 5 of i
            if((avePos > (i - 3)) && (avePos <= (i + 2))) {
                Serial.print("*");
            }
            else {
                Serial.print("-");
            }
        }
        else if( i == 0 ) {
        //if avePos within 5 of i
            if((avePos > (i - 3)) && (avePos <= (i + 2))) {
                Serial.print("*");
            }
            else {
                Serial.print("+");
            }
        }
        else if( i > 0 ) {
        //if avePos within 5 of i
            if((avePos > (i - 3)) && (avePos <= (i + 2))) {
                Serial.print("*");
            }
            else {
                Serial.print("-");
            }
        }
    }
    Serial.print(" avePos = ");
    Serial.println(avePos);
    }
}