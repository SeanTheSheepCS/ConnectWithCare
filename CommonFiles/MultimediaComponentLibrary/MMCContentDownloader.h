#ifndef MMCCONTENT_DOWNLOADER_H
#define MMCCONTENT_DOWNLOADER_H

class MMCContentDownloader
{
	public:
		void beginMultimediaComponentDownloadWithID(unsigned long int multimediaComponentID);
		void makeContributonToFileWithID(unsigned long int multimediaComponentID);
		void endMultimediaComponentDownloadWithID(unsigned long int multimediaComponentID);
	protected:
		//
	private:
		//
};

#endif
