#ifndef MMCCONTENT_DOWNLOADER_H
#define MMCCONTENT_DOWNLOADER_H

#include <fstream>

class MMCContentDownloader
{
	public:
		void beginMultimediaComponentDownloadWithID(unsigned long int multimediaComponentID);
		void makeContributonToFileWithID(unsigned long int multimediaComponentID);
		void hasMultimediaContentDownloadWithIDEnded(unsigned long int multimediaComponentID);
	protected:
		//
	private:
		bool IsADownloadInProgress;
		unsigned long int multimediaComponentIDcurrentlyBeingDownloaded;
		std::ofstream multimediaFileWriter;
};

#endif
