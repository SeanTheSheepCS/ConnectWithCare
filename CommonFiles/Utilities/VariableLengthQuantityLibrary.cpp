#include "VariableLengthQuantityLibrary.h"
#include <iostream>

VariableLengthQuantityConverter::VariableLengthQuantityConverter()
{
	variableLengthQuantityByteLengthOfLastConversion = 0;
	arrayLenthOfVLQValueFromLastConversion = 0;
}

unsigned long int VariableLengthQuantityConverter::convertVariableLengthQuantityToUnsignedLongInt(const unsigned char* messageDataStartingAtVariableLengthQuantityValue)
{
	unsigned char firstElement = messageDataStartingAtVariableLengthQuantityValue[0];

	if((firstElement & 0x80) == 0x00) //If the first element is the only byte in use...
	{
		variableLengthQuantityByteLengthOfLastConversion = 1;
		return (unsigned long int)firstElement;
	}
	else
	{
		unsigned short int maximumNumberOfBytesToProcess = 4; //Any more that four bytes cannot be represented with an unsigned long int. In reality, we can accept 4 and a half. This means the max data length is about 260 million bytes or about 260MB.
		char* arrayOfValues = new char[4];
		arrayOfValues[0] = firstElement & 0x7F;
		for(int currentIndex = 1; currentIndex < maximumNumberOfBytesToProcess; currentIndex++)
		{
			arrayOfValues[currentIndex] = messageDataStartingAtVariableLengthQuantityValue[currentIndex] & 0x7F;
			if((messageDataStartingAtVariableLengthQuantityValue[currentIndex] & 0x80) == 0) //If this is the last byte...
			{
				long int sum = 0;
				int iterationNumber = 0;
				for(int i = currentIndex; i >= 0; i--)
				{
					sum = sum + (((unsigned long int)arrayOfValues[i]) << ( 7 * iterationNumber));
					iterationNumber++;
				}
				variableLengthQuantityByteLengthOfLastConversion = currentIndex+1;
				return sum;
			}
		}
		// If you got here, you number is too large to be represented with a long int :(
		std::cerr << "ERROR: VARIABLE LENGTH QUANTITY VALUE EXCEEDING 260MB DETECTED, THIS IS MOST LIKELY AN ERROR WITH THE DATA LENGTH. PORTIONS OF MESSAGE MAY BE LOST" << std::endl;
		return 0;
	}
}

unsigned short int VariableLengthQuantityConverter::getVariableLengthQuantityByteLengthOfLastConversionFromVLQToUnsignedLongInt()
{
	return variableLengthQuantityByteLengthOfLastConversion;
}

unsigned char* VariableLengthQuantityConverter::convertUnsignedLongIntToVariableLengthQuantity(unsigned long int valueToTurnIntoVariableLengthQuantity)
{
	//Determining the length array we will need
	unsigned short int lengthOfArrayWeWillNeed = 1;
	if(valueToTurnIntoVariableLengthQuantity >= (1<<29))
	{
		lengthOfArrayWeWillNeed = 5;
	}
	else if(valueToTurnIntoVariableLengthQuantity >= (1<<22))
	{
		lengthOfArrayWeWillNeed = 4;
	}
	else if(valueToTurnIntoVariableLengthQuantity >= (1<<15))
	{
		lengthOfArrayWeWillNeed = 3;
	}
	else if(valueToTurnIntoVariableLengthQuantity >= (1<<8))
	{
		lengthOfArrayWeWillNeed = 2;
	}

	unsigned char* vlqArray = new unsigned char[lengthOfArrayWeWillNeed];
	for(int i = 0; i < lengthOfArrayWeWillNeed; i++)
	{
		if(i == lengthOfArrayWeWillNeed - 1) //If we are on the last element of the array...
		{
			//We don't make the first bit a one.
			int shiftAmount = (lengthOfArrayWeWillNeed - i - 1) * 7;
			vlqArray[i] = (unsigned char) valueToTurnIntoVariableLengthQuantity >> shiftAmount;
			vlqArray[i] &= ~0x80;
		}
		else
		{
			//Be sure to make the first bit of the char a 1.
			int shiftAmount = (lengthOfArrayWeWillNeed - i - 1) * 7;
			vlqArray[i] = (unsigned char) valueToTurnIntoVariableLengthQuantity >> shiftAmount;
			vlqArray[i] |= 0x80;
		}
	}
	arrayLenthOfVLQValueFromLastConversion = lengthOfArrayWeWillNeed;
	return &(vlqArray[0]);
}

unsigned short int VariableLengthQuantityConverter::getArrayLengthFromLastConversionFromUnsignedLongIntToVLQ()
{
	return arrayLenthOfVLQValueFromLastConversion;
}

