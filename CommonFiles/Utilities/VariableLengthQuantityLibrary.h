#ifndef VARIABLE_LENGTH_QUANTITY_LIBRARY_H
#define VARIABLE_LENGTH_QUANTITY_LIBRARY_H

class VariableLengthQuantityConverter
{
	public:
		VariableLengthQuantityConverter();
		static unsigned long int convertVariableLengthQuantityToUnsignedLongInt(const unsigned char* messageDataStartingAtVariableLengthQuantityValue);
		static unsigned short int getVariableLengthQuantityByteLengthOfLastConversionFromVLQToUnsignedLongInt();
		static unsigned char* convertUnsignedLongIntToVariableLengthQuantity(unsigned long int valueToTurnIntoVariableLengthQuantity);
		static unsigned short int getArrayLengthFromLastConversionFromUnsignedLongIntToVLQ();
	protected:

	private:
		static unsigned short int veriableLengthQuantityByteLengthOfLastConversion;
};

#endif
