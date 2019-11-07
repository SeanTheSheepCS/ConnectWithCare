#include "ClientRequestMessages.h"

ClientRequestMessage::ClientRequestMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg) : Message(lengthArg, messageAsCharArrayArg)
{
	// 1 byte is message code, 5 bytes are start date, 5 bytes are end date, followed by data length and data.
	const unsigned char* messageCharArray = Message::getMessageAsCharArray();
	messageCode = messageCharArray[0];
	const unsigned char startDateFirstEightBits = messageCharArray[1];
	const unsigned char startDateSecondEightBits = messageCharArray[2];
	const unsigned char startDateThirdEightBits = messageCharArray[3];
	const unsigned char startDateFourthEightBits = messageCharArray[4];
	const unsigned char startDateFifthEightBits = messageCharArray[5];
	// 14 bits at the start are a binary representation of the year.
	unsigned short int startYear = (startDateFirstEightBits << 6) + ((startDateSecondEightBits & 0xFC) >> 2);
	// next 4 bits are a binary representation of the month.
	unsigned short int startMonth = ((startDateSecondEightBits & 0x3) << 2) + ((startDateThirdEightBits & 0xC0) >> 6);
	// next 5 bits are a binary representation of the day
	unsigned short int startDay = ((startDateThirdEightBits & 0x3E) >> 1);
	// next 17 bits are a binary representation of the seconds.
	unsigned long int startSeconds = ((startDateThirdEightBits & 0x01) << 16) + ((startDateFourthEightBits) << 8) + (startDateFifthEightBits);
	startDate = new Date(startYear, startMonth, startDay, startSeconds);

	const unsigned char endDateFirstEightBits = messageCharArray[6];
	const unsigned char endDateSecondEightBits = messageCharArray[7];
	const unsigned char endDateThirdEightBits = messageCharArray[8];
	const unsigned char endDateFourthEightBits = messageCharArray[9];
	const unsigned char endDateFifthEightBits = messageCharArray[10];
	// 14 bits at the start are a binary representation of the year.
	unsigned short int endYear = (endDateFirstEightBits << 6) + ((endDateSecondEightBits & 0xFC) >> 2);
	// next 4 bits are a binary representation of the month.
	unsigned short int endMonth = ((endDateSecondEightBits & 0x3) << 2) + ((endDateThirdEightBits & 0xC0) >> 6);
	// next 5 bits are a binary representation of the day
	unsigned short int endDay = ((endDateThirdEightBits & 0x3E) >> 1);
	// next 17 bits are a binary representation of the seconds.
	unsigned long int endSeconds = ((endDateThirdEightBits & 0x01) << 16) + ((endDateFourthEightBits) << 8) + (endDateFifthEightBits);
	endDate = new Date(endYear, endMonth, endDay, endSeconds);

	dataLengthInBytes = Message::vlqConverter.convertVariableLengthQuantityToUnsignedLongInt(&(messageCharArray[11]));
	indexOfFirstData = 1 /* FOR THE MESSAGE CODE*/ + 5 /* FOR THE START DATE*/ + 5 /* FOR THE END DATE */ + Message::vlqConverter.getVariableLengthQuantityByteLengthOfLastConversionFromVLQToUnsignedLongInt();
}

ClientRequestMessage::ClientRequestMessage(const ClientRequestMessage& other) : Message(other)
{
	this->messageCode = other.messageCode;
	this->startDate = new Date(other.startDate->getYear(), other.startDate->getMonth(), other.startDate->getDay(), other.startDate->getSeconds());
	this->endDate = new Date(other.endDate->getYear(), other.endDate->getMonth(), other.endDate->getDay(), other.endDate->getSeconds());
}

ClientRequestMessage& ClientRequestMessage::operator=(const ClientRequestMessage& rhs)
{
	if(this != &rhs)
	{
		delete startDate;
		delete endDate;
		this->messageCode = rhs.messageCode;
		this->startDate = new Date(rhs.startDate->getYear(), rhs.startDate->getMonth(), rhs.startDate->getDay(), rhs.startDate->getSeconds());
		this->endDate = new Date(rhs.endDate->getYear(), rhs.endDate->getMonth(), rhs.endDate->getDay(), rhs.endDate->getSeconds());
	}
	return *this;
}

ClientRequestMessage::~ClientRequestMessage()
{
	messageCode = 0;
	dataLengthInBytes = 0;
	indexOfFirstData = 0;
	delete startDate;
	delete endDate;
}

unsigned char ClientRequestMessage::getMessageCode()
{
	return messageCode;
}

unsigned long int ClientRequestMessage::getDataLengthInBytes()
{
	return dataLengthInBytes;
}

unsigned long int ClientRequestMessage::getIndexOfFirstData()
{
	return indexOfFirstData;
}

const Date ClientRequestMessage::getStartDate()
{
	return *startDate;
}

const Date ClientRequestMessage::getEndDate()
{
	return *endDate;
}
