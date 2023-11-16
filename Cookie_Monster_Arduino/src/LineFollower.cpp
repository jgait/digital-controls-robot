#include "LineFollower.h"
#include <Arduino.h>

// Constructor
LineArray::LineArray() : mySensorBar(SX1509_ADDRESS) {}

void LineArray::init(){ 
    mySensorBar.setBarStrobe();
    //Default dark on light
    mySensorBar.clearInvertBits();
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
    uint8_t raw_data = mySensorBar.getRaw();
    positionHistory.pushElement(raw_data);
    
    return raw_data;
}

uint8_t* LineArray::getArray(){
    return positionHistory.getArray();
}

uint8_t LineArray::getHeading(){
    return positionHistory.getHeading();
}


int LineArray::algoPureSum(int raw) {
    int read = 0;
    /*
    dummy check raw
    if the value is bad: (as in, on a gap OR cross)
        look at history first
    else:
        continue as normal
    */
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