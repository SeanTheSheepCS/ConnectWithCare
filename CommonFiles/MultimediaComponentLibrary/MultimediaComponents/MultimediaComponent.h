#ifndef COMMONFILES_MULTIMEDIACOMPONENTLIBRARY_MULTIMEDIACOMPONENTS_MULTIMEDIACOMPONENT_H_
#define COMMONFILES_MULTIMEDIACOMPONENTLIBRARY_MULTIMEDIACOMPONENTS_MULTIMEDIACOMPONENT_H_

#include <string>

class MultimediaComponent
{
	public:
		MultimediaComponent(std::string filenameArg, unsigned long int multimediaComponentIDArg, unsigned char* terminatorArrayArg, unsigned short int lengthOfTerminatorArrayArg);
		MultimediaComponent(const MultimediaComponent& other);
		virtual MultimediaComponent& operator=(const MultimediaComponent& rhs);
		virtual ~MultimediaComponent();
		std::string getFilename() const;
		unsigned long int getMultimediaComponentID() const;
		const unsigned char* getTerminatorArray() const;
		const unsigned short int getLengthOfTerminatorArray() const;
	protected:
		unsigned char* terminatorArray;
		unsigned short int lengthOfTerminatorArray;
		//FOR USE BY SUBCLASSES OF MultimediaComponent ONLY. THEY MUST INITIALIZE THE TERMINATOR ARRAY AND LENGTH AFTERWARDS THOUGH
		MultimediaComponent(std::string filenameArg, unsigned long int multimediaComponentIDArg);
	private:
		std::string filename;
		unsigned long int multimediaComponentID;
};

#endif /* COMMONFILES_MULTIMEDIACOMPONENTLIBRARY_MULTIMEDIACOMPONENTS_MULTIMEDIACOMPONENT_H_ */
