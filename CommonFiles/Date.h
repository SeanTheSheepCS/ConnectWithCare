#ifndef DATE_H
#define DATE_H

#include <string>

class Date
{
	public:
		Date(unsigned short int year, unsigned short int month, unsigned short int day, unsigned long int seconds);
		unsigned short int getYear() const;
		unsigned short int getMonth() const;
		unsigned short int getDay() const;
		unsigned long int getSeconds() const;
		bool equals(const Date other) const;
		bool isBefore(const Date other) const;
		bool isAfter(const Date other) const;
		std::string toString() const;
		const unsigned char* toFiveByteFormat() const;
	protected:
		//
	private:
		unsigned short int year;
		unsigned short int month;
		unsigned short int day;
		unsigned long int seconds;
};

#endif
