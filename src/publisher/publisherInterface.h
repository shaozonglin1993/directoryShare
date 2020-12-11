#ifndef FILE_PUBLISHER_INTERFACE_H
#define FILE_PUBLISHER_INTERFACE_H

#include <sstream>
#include "../CommonInfrastructure/DDSCommunicator.h"
#include "../CommonInfrastructure/DDSTypeWrapper.h"

class FilePublisherDiscoveryListener;
class CodecCompatibleHandler;

class FilePublisherInterface
{

public:

	// --- Constructor --- 
	// Initializes the video publisher interface, including creating a 
	// DomainParticipant, creating all publishers and subscribers, topics 
	// writers and readers.  Takes as input a vector of xml QoS files that
	// should be loaded to find QoS profiles and libraries.
	FilePublisherInterface(std::vector<std::string> xmlFiles,
			CodecCompatibleHandler *codecCompatibilityHandler = NULL);

	// --- Destructor --- 
	~FilePublisherInterface();

	// --- Getter for Communicator --- 
	// Accessor for the communicator (the class that sets up the basic
	// DDS infrastructure like the DomainParticipant).
	// This allows access to the DDS DomainParticipant/Publisher/Subscriber
	// classes
	DDSCommunicator *GetCommunicator() 
	{ 
		return _communicator; 
	}

	// --- Sends the video data ---
	// Uses DDS interface to send a video stream efficiently over the 
	// network or shared memory to interested applications subscribing to
	// streaming video.
	bool Write(DdsAutoType<FileData> data);

	// --- Deletes the video stream ---
	// "Deletes" the video stream from the system - removing the DDS 
	// instance from all applications.
	bool Delete(DdsAutoType<FileData> data);

private:
	// --- Private members ---

	// Used to create basic DDS entities that all applications need
	DDSCommunicator *_communicator;

	// Video stream publisher specific to this application
	FileDataWriter *_writer;
};


class CodecCompatibleHandler
{
public:
	virtual bool CodecsCompatible(std::string codecString) = 0;
};

// ------------------------------------------------------------------------- //
//
// The video publisher discovery listener is used to listen to discovery of
// remote video subscriber applications.  
//
// Listening for video metadata:
// -----------------------------
//
// This is a listener that is installed on the local DomainParticipant.  It is
// notified when the DomainParticipant discovers a remote DataReader.  At that
// time, it checks whether the DataReader:
//        1) Has a topic that this application interested in (VIDEO_TOPIC)
//        2) Has sent metadata as a part of the discovery data using the 
//           user_data QoS.  This metadata should include information about the
//           codecs that the reader can decode.  If the DataReader does not 
//           support a codec that this application is writing, we will print an
//           error, and we will not send video data to the DataReader.
//
// ------------------------------------------------------------------------- //
class FilePublisherDiscoveryListener : public DDS::DataReaderListener
{
public:

	// --- Constructor --- 
	FilePublisherDiscoveryListener(CodecCompatibleHandler *handler)
		: _handler(handler)
	{
	}

	// --- Listener callback for discovery of remote DataReader --- 
	// Inherited from the DDSDataReaderListener class
	virtual void on_data_available(DDS::DataReader *reader);

private:
	CodecCompatibleHandler *_handler;
};

#endif