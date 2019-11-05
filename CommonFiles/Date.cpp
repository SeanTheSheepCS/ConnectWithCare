#include "Date.h"

Date::Date(unsigned short int year, unsigned short int month, unsigned short int day, unsigned long int seconds)
{
	this->year = year;
	this->month = month;
	this->day = day;
	this->seconds = seconds;
}

unsigned short int Date::getYear()
{
	return year;
}

unsigned short int Date::getMonth()
{
	return month;
}

unsigned short int Date::getDay()
{
	return day;
}

unsigned long int Date::getSeconds()
{
	return seconds;
}

bool Date::equals(Date other)
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

bool Date::isBefore(Date other)
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

bool Date::isAfter(Date other)
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

string Date::Print()
{
	string toPrint;
	toPrint = (this->day)->ToString() + "/" + (this->month)->ToString() + "/" + (this->year)->ToString();
	return toPrint;
}
