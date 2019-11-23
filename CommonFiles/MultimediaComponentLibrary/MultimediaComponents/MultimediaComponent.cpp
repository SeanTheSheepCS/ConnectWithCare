#include "MultimediaComponent.h"

#include <string>


MultimediaComponent::MultimediaComponent(std::string filenameArg, int multimediaComponentIDArg)
{
	this->filename = std::string(filenameArg);
	this->multimediaComponentID = multimediaComponentIDArg;
}

std::string MultimediaComponent::getFilename()
{
	return filename;
}

unsigned long int MultimediaComponent::getMultimediaComponentID()
{
	return multimediaComponentID;
}
