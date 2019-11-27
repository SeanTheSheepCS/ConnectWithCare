#ifndef COMMONFILES_MULTIMEDIACOMPONENTLIBRARY_MULTIMEDIACOMPONENTS_MMCIMAGEJPEG_H_
#define COMMONFILES_MULTIMEDIACOMPONENTLIBRARY_MULTIMEDIACOMPONENTS_MMCIMAGEJPEG_H_

#include <string>
#include "MultimediaComponent.h"

class MMCImageJPEG : public MultimediaComponent
{
	public:
		MMCImageJPEG(std::string filenameArg, unsigned long int multimediaComponentIDArg);

		// BELOW FUNCTIONS ARE NOT STRICTLY NEEDED BUT IF YOU WANT THEM YOU CAN UNCOMMENT AND IMPLEMENT THEM IN THE CPP FILE.

		//virtual MMCImageJPEG(const MMCImageJPEG& other);
		//virtual MMCImageJPEG& operator=(const MMCImageJPEG& rhs);
		//virtual ~MMCImageJPEG();
	protected:
		//
	private:
		//
};

#endif /* COMMONFILES_MULTIMEDIACOMPONENTLIBRARY_MULTIMEDIACOMPONENTS_MMCIMAGEJPEG_H_ */
