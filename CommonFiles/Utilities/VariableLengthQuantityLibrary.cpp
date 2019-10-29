#include "VariableLengthQuantityLibrary.h"
#include <iostream>

VariableLengthQuantityConverter::VariableLengthQuantityConverter()
{
	veriableLengthQuantityByteLengthOfLastConversion = 0;
}

unsigned long int VariableLengthQuantityConverter::convertVariableLengthQuantityToUnsignedLongInt(unsigned char* messageDataStartingAtVariableLengthQuantityValue)
{
	unsigned char firstElement = messageDataStartingAtVariableLengthQuantityValue[0];

	if((firstElement & 0x80) == 0x00) //If the first element is the only byte in use...
	{
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
				veriableLengthQuantityByteLengthOfLastConversion = currentIndex+1;
				return sum;
			}
		}
		// If you got here, you number is too large to be represented with a long int :(
		std::cerr << "ERROR: VARIABLE LENGTH QUANTITY VALUE EXCEEDING 260MB DETECTED, THIS IS MOST LIKELY AN ERROR WITH THE DATA LENGTH. PORTIONS OF MESSAGE MAY BE LOST" << std::endl;
		return 0;
	}
}

unsigned short int VariableLengthQuantityConverter::getVariableLengthQuantityByteLengthOfLastConversion()
{
	return veriableLengthQuantityByteLengthOfLastConversion;
}

unsigned char* convertUnsignedLongIntToVariableLengthQuantity(unsigned long int valueToTurnIntoVariableLengthQuantity)
{

}

unsigned short int getArrayLengthFromLastConversionFromUnsignedLongIntToVLQ()
{

}

