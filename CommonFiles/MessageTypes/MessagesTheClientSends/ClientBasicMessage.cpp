#include "ClientBasicMessages.h"

ClientBasicMessage::ClientBasicMessage(Message messageToTurnIntoClientBasicMessage) : Message(messageToTurnIntoClientBasicMessage)
{
	char[] messageCharArray = getMessageAsCharArray;
	//Reading message code
	messageCode = messageCharArray[0];
	//Reading the data length (variable length quantity)
	char** beforeCallToTheVariableLengthQuantityFunctionWillPointToStartOfVariableLengthQuantityAfterCallWillPointToValueAfter = &(messageCharArray[1]);
	dataLengthInBytes = convertVariableLengthQuantityToUnsignedLongIntAndMoveTheIndexPastTheVariableLengthQuantityValue(beforeCallToTheVariableLengthQuantityFunctionWillPointToStartOfVariableLengthQuantityAfterCallWillPointToValueAfter);
	//messageCharArray our beforeCallAfterCall variable should now be advanced to the index of the first data. This subtraction should return the index where the data begins.
	indexOfFirstData = (*beforeCallToTheVariableLengthQuantityFunctionWillPointToStartOfVariableLengthQuantityAfterCallWillPointToValueAfter)-(&messageCharArray[0]);
}

unsigned char getMessageCode()
{
	return messageCode;
}

unsigned long int getDataLengthInBytes()
{
	return dataLengthInBytes;
}

unsigned long int getIndexOfFirstData()
{
	return indexOfFirstData;
}
