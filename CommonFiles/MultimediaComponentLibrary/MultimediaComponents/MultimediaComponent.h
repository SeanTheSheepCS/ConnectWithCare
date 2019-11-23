#ifndef COMMONFILES_MULTIMEDIACOMPONENTLIBRARY_MULTIMEDIACOMPONENTS_MULTIMEDIACOMPONENT_H_
#define COMMONFILES_MULTIMEDIACOMPONENTLIBRARY_MULTIMEDIACOMPONENTS_MULTIMEDIACOMPONENT_H_

#include <string>

class MultimediaComponent
{
	public:
		MultimediaComponent(std::string filenameArg, int multimediaComponentIDArg);
		std::string getFilename();
		unsigned long int getMultimediaComponentID();
	protected:
		//
	private:
		std::string filename;
		unsigned long int multimediaComponentID;
};

#endif /* COMMONFILES_MULTIMEDIACOMPONENTLIBRARY_MULTIMEDIACOMPONENTS_MULTIMEDIACOMPONENT_H_ */
