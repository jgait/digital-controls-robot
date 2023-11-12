#include "LineFollower.h"
#include <Arduino.h>

// Constructor
LineArray::LineArray() : mySensorBar(SX1509_ADDRESS) {}

void LineArray::init(){ 
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
        Serial.println("The line sensor is good to go!");
    }
    else
    {
        Serial.println("The line sensor I2C communication FAILED! :(");
        while(1);
    }
}

int LineArray::readRaw(){
    //Get the data from the bar and save it to the circular buffer positionHistory.
    return mySensorBar.getRaw();
}

int LineArray::algoPureSum(int raw) {
    int read = 0;
    for (int i = 0; i < 8; ++i) {
        // Check if the ith bit of SenseRead is set
        if (raw & (1 << i)) {
            read += weights[7-i];
        }
    }

    return read;
}

int LineArray::algoMaxErr(int raw) {
    int read = 0;
    for (int i = 0; i < 8; ++i) {
        // Check if the ith bit of SenseRead is set
        if (raw & (1 << i)) {
            // if so get the weight and if it is larger than current read set read to it
            int weight = weights[7-i];
            if(abs(weight) > abs(read)) {
                read = weight;
            }
        }
    }

    return read;
}