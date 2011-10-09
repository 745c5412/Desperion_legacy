#ifndef __IDENTIFICATION_MESSAGE__
#define __IDENTIFICATION_MESSAGE__

class IdentificationMessage : public DofusMessage
{
public:
	Version version;
	std::map<int, std::string> certificates;
	std::string userName;
	std::string password;
	bool autoConnect;

	uint32 GetOpcode() const
	{ return CMSG_IDENTIFICATION; }

	IdentificationMessage(ByteBuffer& data)
	{
		version.Init(data);
		uint16 certificateLength;
		data>>userName>>password>>certificateLength;
		for(uint16 a = 0; a < certificateLength; ++a)
		{
			uint32 id;
			std::string hash;
			data>>id>>hash;
			certificates[id] = hash;
		}
		data>>autoConnect;
	}
};

#endif