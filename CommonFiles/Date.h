#ifndef DATE_H
#define DATE_H

#include <string>

class Date
{
	public:
		Date(unsigned short int year, unsigned short int month, unsigned short int day, unsigned long int seconds);
		unsigned short int getYear();
		unsigned short int getMonth();
		unsigned short int getDay();
		unsigned long int getSeconds();
		bool equals(Date other);
		bool isBefore(Date other);
		bool isAfter(Date other);
		std::string toString();
	protected:
		//
	private:
		unsigned short int year;
		unsigned short int month;
		unsigned short int day;
		unsigned long int seconds;
};

#endif
