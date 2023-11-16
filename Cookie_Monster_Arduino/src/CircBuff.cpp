#include "CircBuff.h"


//Construct a CircBuff type with arguments
//  uint16_t inputSize: number of elements
CircBuff::CircBuff(uint8_t inputSize)
{
	cBufferData = new uint8_t[inputSize];
	cBufferLastPtr = 0;
	cBufferElementsUsed = 0;  
	cBufferSize = inputSize;
	
}

CircBuff::~CircBuff()
{
	delete[] cBufferData;

}

//Get an element at some depth into the circular buffer
//zero is the push location.  Max is cBufferSize - 1
//
//Arguments:
//  uint16_t elementNum: number of element in
//
uint8_t CircBuff::getElement( uint8_t elementNum )
{
  //Translate elementNum into terms of cBufferLastPtr.
  uint8_t virtualElementNum;
  virtualElementNum = cBufferLastPtr - elementNum;
  if( virtualElementNum < 0 )
  {
    virtualElementNum += cBufferSize;
  }
  
  //Output the value
  return cBufferData[virtualElementNum];
}

//Put a new element into the buffer.
//This also expands the size up to the max size
//Arguments:
//
//  int16_t elementVal: value of new element
//
void CircBuff::pushElement( uint8_t elementVal )
{
  //inc. the pointer
  cBufferLastPtr++;

  //deal with roll
  if( cBufferLastPtr >= cBufferSize )
  {
    cBufferLastPtr = 0;
  }

  //write data
  cBufferData[cBufferLastPtr] = elementVal;

  //increase length up to cBufferSize
  if( cBufferElementsUsed < cBufferSize )
  {
    cBufferElementsUsed++;
  }
}

//Averages the last n numbers and provides that.  Discards fractions
uint8_t CircBuff::averageLast( uint8_t numElements )
{
  //Add up all the elements
  int32_t accumulator = 0;
  int8_t i;
  for( i = 0; i < numElements; i++ )
  {
    accumulator += getElement( i );
  }
  //Divide by number of elements
  accumulator /= numElements;
  return accumulator;
}

//Returns the current size of the buffer
uint8_t CircBuff::recordLength( void )
{
  return cBufferElementsUsed;
}

uint8_t* CircBuff::getArray()
{
  return cBufferData;
}

uint8_t CircBuff::getHeading()
{
  return cBufferLastPtr;
}
