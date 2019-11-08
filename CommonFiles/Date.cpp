#include "Date.h"
#include <string>

Date::Date(unsigned short int year, unsigned short int month, unsigned short int day, unsigned long int seconds)
{
	this->year = year;
	this->month = month;
	this->day = day;
	this->seconds = seconds;
}

Date::Date(const unsigned char* fiveByteFormat)
{
	const unsigned char dateFirstEightBits = fiveByteFormat[0];
	const unsigned char dateSecondEightBits = fiveByteFormat[1];
	const unsigned char dateThirdEightBits = fiveByteFormat[2];
	const unsigned char dateFourthEightBits = fiveByteFormat[3];
	const unsigned char dateFifthEightBits = fiveByteFormat[4];
	// 14 bits at the start are a binary representation of the year.
	unsigned short int dateYear = (dateFirstEightBits << 6) + ((dateSecondEightBits & 0xFC) >> 2);
	// next 4 bits are a binary representation of the month.
	unsigned short int dateMonth = ((dateSecondEightBits & 0x3) << 2) + ((dateThirdEightBits & 0xC0) >> 6);
	// next 5 bits are a binary representation of the day
	unsigned short int dateDay = ((dateThirdEightBits & 0x3E) >> 1);
	// next 17 bits are a binary representation of the seconds.
	unsigned long int dateSeconds = ((dateThirdEightBits & 0x01) << 16) + ((dateFourthEightBits) << 8) + (dateFifthEightBits);

	this->year = dateYear;
	this->month = dateMonth;
	this->day = dateDay;
	this->seconds = dateSeconds;
}

unsigned short int Date::getYear() const
{
	return year;
}

unsigned short int Date::getMonth() const
{
	return month;
}

unsigned short int Date::getDay() const
{
	return day;
}

unsigned long int Date::getSeconds() const
{
	return seconds;
}

bool Date::equals(const Date other) const
{
	if((this->year == other.year) && (this->month == other.month) && (this->day == other.day) && (this->seconds == other.seconds))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Date::isBefore(const Date other) const
{
	if(this->year == other.year)
	{
		if(this->month == other.month)
		{
			if(this->day == other.day)
			{
				if(this->seconds == other.seconds)
				{
					return false;
				}
				else if(this->seconds > other.seconds)
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			else if(this->day > other.day)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		else if(this->month > other.month)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else if(this->year > other.year)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Date::isAfter(const Date other) const
{
	if(this->year == other.year)
	{
		if(this->month == other.month)
		{
			if(this->day == other.day)
			{
				if(this->seconds == other.seconds)
				{
					return false;
				}
				else if(this->seconds > other.seconds)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else if(this->day > other.day)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if(this->month > other.month)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if(this->year > other.year)
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::string Date::toString() const
{
	std::string toPrint;
	toPrint = std::to_string(this->day) + "/" + std::to_string(this->month) + "/" + std::to_string(this->year);
	return toPrint;
}

const unsigned char* Date::toFiveByteFormat() const
{
	unsigned char* charArray = new unsigned char[5];
	for(int i = 0; i < 5; i++)
	{
		charArray[i] = 0;
	}
	//First 14 bits are for year
	charArray[0] |= (year >> 6);
	charArray[1] |= (year) << 2;
	//Next 4 bits are for month
	charArray[1] |= (month >> 2);
	charArray[2] |= (month) << 6;
	//Next 5 bits are for day
	charArray[2] |= (day) << 1;
	//Next 17 bits are for seconds
	charArray[2] |= (seconds << 16);
	charArray[3] |= (seconds << 8);
	charArray[4] |= (seconds);

	return charArray;
}
