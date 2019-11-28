#include "MultimediaComponent.h"

#include <string>


MultimediaComponent::MultimediaComponent(std::string filenameArg, unsigned long int multimediaComponentIDArg, unsigned char* terminatorArrayArg, unsigned short int lengthOfTerminatorArrayArg)
{
	this->filename = std::string(filenameArg);
	this->multimediaComponentID = multimediaComponentIDArg;
	this->terminatorArray = new unsigned char[lengthOfTerminatorArrayArg];
	for(unsigned short int i = 0; i < lengthOfTerminatorArrayArg; i++)
	{
		(this->terminatorArray)[i] = terminatorArrayArg[i];
	}
	this->lengthOfTerminatorArray = lengthOfTerminatorArrayArg;
}


// I AM PROTECTED, FOR USE BY SUBCLASSES OF MultimediaComponent ONLY. THEY MUST INITIALIZE THE TERMINATOR ARRAY AND LENGTH AFTERWARDS THOUGH
MultimediaComponent::MultimediaComponent(std::string filenameArg, unsigned long int multimediaComponentIDArg)
{
	filename = filenameArg;
	multimediaComponentID = multimediaComponentIDArg;
	terminatorArray = nullptr;
	lengthOfTerminatorArray = 0;
}

std::string MultimediaComponent::getFilename() const
{
	return filename;
}

unsigned long int MultimediaComponent::getMultimediaComponentID() const
{
	return multimediaComponentID;
}

const unsigned char* MultimediaComponent::getTerminatorArray() const
{
	return terminatorArray;
}

const unsigned short int MultimediaComponent::getLengthOfTerminatorArray() const
{
	return lengthOfTerminatorArray;
}

MultimediaComponent::MultimediaComponent(const MultimediaComponent& other)
{
	this->filename = other.filename;
	this->multimediaComponentID = other.multimediaComponentID;
	this->terminatorArray = new unsigned char[other.lengthOfTerminatorArray];
	for(unsigned short int i = 0; i < other.lengthOfTerminatorArray; i++)
	{
		(this->terminatorArray)[i] = other.terminatorArray[i];
	}
	this->lengthOfTerminatorArray = other.lengthOfTerminatorArray;
}

MultimediaComponent& MultimediaComponent::operator=(const MultimediaComponent& rhs)
{
	if(this != &rhs)
	{
		delete[] terminatorArray;
		this->filename = rhs.filename;
		this->multimediaComponentID = rhs.multimediaComponentID;
		this->terminatorArray = new unsigned char[rhs.lengthOfTerminatorArray];
		for(unsigned short int i = 0; i < rhs.lengthOfTerminatorArray; i++)
		{
			(this->terminatorArray)[i] = rhs.terminatorArray[i];
		}
		this->lengthOfTerminatorArray = rhs.lengthOfTerminatorArray;
	}
	return *this;
}

MultimediaComponent::~MultimediaComponent()
{
	delete[] terminatorArray;
	filename = "";
	multimediaComponentID = 0;
	lengthOfTerminatorArray = 0;
}
