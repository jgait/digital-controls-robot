#ifndef CIRCBUFF_H
#define CIRCBUFF_H

#include "stdint.h"



class CircBuff
{
public:
    CircBuff( uint8_t inputSize );
	~CircBuff();
    uint8_t getElement( uint8_t ); //zero is the push location
    void pushElement( uint8_t );
    uint8_t averageLast( uint8_t );
    uint8_t recordLength( void );
    uint8_t* getArray();
    uint8_t getHeading();
private:
	uint8_t cBufferSize;
    uint8_t *cBufferData;
    uint8_t cBufferLastPtr;
    uint8_t cBufferElementsUsed;
};


#endif