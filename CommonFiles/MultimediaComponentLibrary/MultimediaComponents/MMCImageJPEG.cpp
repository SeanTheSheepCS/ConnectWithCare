#include "MMCImageJPEG.h"
#include "MultimediaComponent.h"
#include <string>

MMCImageJPEG::MMCImageJPEG(std::string filenameArg, unsigned long int multimediaComponentIDArg) : MultimediaComponent(filenameArg, multimediaComponentIDArg)
{
	MultimediaComponent::terminatorArray = new unsigned char[2];
	MultimediaComponent::terminatorArray[0] = 0xFF;
	MultimediaComponent::terminatorArray[1] = 0xD9;
	lengthOfTerminatorArray = 2;
}

/*
 *
 * BELOW FUNCTIONS ARE NOT NEEDED, IF YOU MAKE CHANGES AND NEED THEM FOR SOME REASON, UNCOMMENT AND IMPLEMENT THEM.
 *
 *
 *
MMCImage::MMCImageJPEG(const MMCImageJPEG& other)
{

}

MMCImageJPEG& MMCImage::operator=(const MMCImageJPEG& rhs)
{

}

MMCImage::~MMCImageJPEG()
{

}

 */
