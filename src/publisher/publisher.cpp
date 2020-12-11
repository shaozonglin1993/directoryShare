#include <stdio.h>
#include <vector>
#include <iostream>

#include "../typefile/VideoData.h"
#include "../typefile/VideoDataSupport.h"
#include "ndds/ndds_cpp.h"
#include "ndds/ndds_namespace_cpp.h"
#include "../common/DDSCommunicator.h"
#include "publisherInterface.h"


using namespace std;

void PrintHelp();

//

class FileHandler : public SHRFileHandler
{
public:
	FileHandler()
	{

	}


	virtual void fileReady(void *obj, file *buffer)
	{
		// Has a copy of the DDS interface that is used to publish data over 
		// the network (or shared memory).
		publisherInterface *pubInterface = 
			(VideoPublisherInterface *)obj;
	}

private:

	int _seqNum;

	int _fileId;
};