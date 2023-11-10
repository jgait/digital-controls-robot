#ifndef LINEFOLLOWER_H
#define LINEFOLLOWER_H

#include <sensorbar.h>

#define CBUFFER_SIZE 100
const uint8_t SX1509_ADDRESS = 0x3E;  // SX1509 I2C address (00)



class LineFollower{

    private:
        SensorBar mySensorBar = SensorBar(SX1509_ADDRESS);
        CircularBuffer positionHistory = CircularBuffer(CBUFFER_SIZE);

    public:
        void init();
        void barReading();    
};


#endif