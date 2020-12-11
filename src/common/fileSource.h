#ifndef FILE_SOURCE_H_
#define FILE_SOURCE_H_

class SHRFileSource 
{
public:

	// --- Constructor --- 
	SHRFileSource(std::string url);

	// --- Initialization --- 
	int Initialize();

	std::string GetFileMetadata();

	// --- Start ---
	int Start();

	// --- Set Frame Callback Handler
	void SetNewFileCallbackHandler(SHRFileHandler *handler, void *obj);

	// --- Getters and setters
	SHRFileHandler *GetFileReadyHandler()
	{
		return _fileReadyHandler;
	}

	void *GetHandlerObj() 
	{
		return _handlerObj;
	}

	FILE *GetFile()
	{
		return _file;
	}

private:


	// --- Private members --- 

	// File path to open
	std::string _url;
	OSThread *_worker;
	SHRFileHandler *_fileReadyHandler;
	void *_handlerObj;

	// file objects
	FILE *_file;

};

#endif /*FILE_SOURCE_H_*/