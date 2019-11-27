#ifndef MMCCONTENT_UPLOADER_H
#define MMCCONTENT_UPLOADER_H

#include <fstream>

class MMCContentUploader
{
	public:
		void beginUploadOfMultimediaComponentWithID(unsigned long int multimediaComponentID);
		unsigned char getNextByteForMultimediaComponentUploadWithID(unsigned long int multimediaComponentID);
		bool isUploadOfMultimediaComponentWithIDOver(unsigned long int multimediaComponentID);
	protected:
		//
	private:
		bool isUploadInProgress;
		unsigned long int multimediaComponentIDcurrentlyBeingUploaded;
		std::ifstream multimediaFileReader;
};

#endif
