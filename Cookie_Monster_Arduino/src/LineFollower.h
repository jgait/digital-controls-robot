#ifndef LINEFOLLOWER_H
#define LINEFOLLOWER_H

#include <sensorbar.h>
#include "CircBuff.h"

#define CBUFFER_SIZE 4
const uint8_t SX1509_ADDRESS = 0x3E;  // SX1509 I2C address (00)

class LineArray{

    private:
        SensorBar mySensorBar;
        CircBuff positionHistory = CircBuff(CBUFFER_SIZE);

        int weights[8] = {-40, -5, -2, -2, 2, 2, 5, 40};

    public:
        LineArray();

        void init();
        int readRaw();    
        uint8_t getAverage();
        uint8_t* getArray();
        uint8_t getHeading();
        int algoPureSum(int raw);
        int algoMaxErr(int raw);
};

#endif