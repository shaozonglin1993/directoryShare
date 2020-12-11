#ifndef FILE_EVENT_H_
#define FILE_EVENT_H_

#include "fileBuffer.h"

// ------------------------------------------------------------------------- //
//
// SHRFileHandler:
//
// Callback functions for different file events.  This is used by both the 
// sender and  receiver, since they both receive files from 
// somewhere 
// 
// ------------------------------------------------------------------------- //
class SHRFileHandler
{
public:
	virtual void fileReady(void *obj, file *buffer) = 0;
};

#endif /* FILE_EVENT_H_ */