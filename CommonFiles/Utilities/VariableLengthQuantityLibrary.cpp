#include "VariableLengthQuantityLibrary.h"

unsigned long int convertVariableLengthQuantityToUnsignedLongIntAndMoveTheIndexPastTheVariableLengthQuantityValue(unsigned char** thisIsAPointerToAPointerThatShouldPointToTheStartOfTheVariableLengthQuantityValueAndShouldBeMovedOneBytePastTheEndOfTheVariableLengthQuantityValue)
{
	unsigned char[] messageStartingAtVariableLengthQuantityValue = *thisIsAPointerToAPointerThatShouldPointToTheStartOfTheVariableLengthQuantityValueAndShouldBeMovedOneBytePastTheEndOfTheVariableLengthQuantityValue;
	unsigned char firstElement = messageStartingAtVariableLengthQuantityValue[0];

	if(firstElement & 0x80 == 0x00) //If the first element is the only byte in use...
	{
		return (unsigned long int)firstElement;
	}
	else
	{
		unsigned short int maximumNumberOfBytesToProcess = 4; //Any more that four bytes cannot be represented with an unsigned long int. In reality, we can accept 4 and a half. This means the max data length is about 260 million bytes or about 260MB.
		char[] arrayOfValues = new char[4];
		arrayOfValues[0] = firstElement & 0x7F;
		for(int currentIndex = 1; currentIndex < maximumNumberOfBytesToProcess; currentIndex++)
		{
			arrayOfValues[currentIndex] = messageStartingAtVariableLengthQuantityValue[currentIndex] & 0x7F;
			if(messageStartingAtVariableLengthQuantityValue[currentIndex] & 0x80 == 0) //If this is the last byte...
			{
				long int sum = 0;
				int iterationNumber = 0;
				for(int i = currentIndex; i >= 0; i--)
				{
					sum = sum + (arrayOfValues[i] << ( 7 * iterationNumber));
					iterationNumber++;
				}
				return sum;
			}
		}
		// If you got here, you number is too large to be represented with a long int :(
		std::cerr << "ERROR: VARIABLE LENGTH QUANTITY VALUE EXCEEDING 260MB DETECTED, THIS IS MOST LIKELY AN ERROR WITH THE DATA LENGTH. PORTIONS OF MESSAGE MAY BE LOST" << std::endl;
		return 0;
	}
}

