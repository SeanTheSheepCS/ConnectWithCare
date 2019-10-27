ClientMessageCreator::ClientMessageCreator()
{

}

LoginMessage ClientMessageCreator::createLoginMessage(std::string username, std::string password)
{
	unsigned char messageCode = CLIENTMESSAGECODE_LOGIN;
	unsigned long int usernameLengthInVLQ = convertUnsignedLongIntToVariableLengthQuantity(username.length());
	unsigned short int usernameLengthLengthInBytes = getArrayLengthFromLastConversionFromUnsignedLongIntToVLQ();
	//unsigned long int passwordLengthInBytes = convertUnsignedLongIntToVariableLengthQuantity(password.length());

	//GUESSES FOR THE VLQ FIELD FOR MESSAGE LENGTH
	unsigned short int guessForVLQFieldForMessageLength = 1;
	unsigned long int totalMessageLengthInBytes = 1 /* FOR THE MESSAGE CODE */ + guessForVLQFieldForMessageLength + usernameLengthLengthInBytes + username.length() + password.length();
	unsigned char* arrayRepresentingMessageLengthInVLQ = convertUnsignedLongIntToVariableLengthQuantity(totalMessageLengthInBytes);
	unsigned short int trueVLQFieldMessageLength = getArrayLengthFromLastConversionFromUnsignedLongIntToVLQ();
	while(guessForVLQFieldForMessageLength != trueVLQFieldMessageLength)
	{
		delete[] arrayRepresentingMessageLengthInVLQ;
		guessForVLQFieldForMessageLength = trueVLQFieldMessageLength;
		totalMessageLengthInBytes = 1 /* FOR THE MESSAGE CODE */ + guessForVLQFieldForMessageLength + usernameLengthLengthInBytes + username.length() + password.length();
		arrayRepresentingMessageLengthInVLQ = convertUnsignedLongIntToVariableLengthQuantity(totalMessageLengthInBytes);
		trueVLQFieldMessageLength = getArrayLengthFromLastConversionFromUnsignedLongIntToVLQ();
	}
	unsigned char[] messageArray = new unsigned char[totalMessageLengthInBytes];
	int currentIndex = 0;
	messageArray[currentIndex] = messageCode;
	currentIndex++;
	for(int i = 0; i < trueVLQFieldMessageLength; i++)
	{
		messageArray[currentIndex] = arrayRepresentingMessageLengthInVLQ[i];
		currentIndex++;
	}
	for(int i = 0; i < usernameLengthLengthInBytes; i++)
	{
		messageArray[currentIndex] = arrayRepresentingMessageLengthInVLQ[i];
		currentIndex++;
	}
	for(int i = 0; i < username.length(); i++)
	{
		messageArray[currentIndex] = username[i];
		currentIndex++;
	}
	for(int i = 0; i < password.length(); i++)
	{
		messageArray[currentIndex] = password[i];
		currentIndex++;
	}

	LoginMessage returnValue = LoginMessage(ClientBasicMessage(Message(totalMessageLengthInBytes,messageArray)));
	delete[] arrayRepresentingMessageLengthInVLQ;
	delete[] messageArray;
	return returnValue;
}
