#ifndef __SERVER_SELECTION_MESSAGE__
#define __SERVER_SELECTION_MESSAGE__

class ServerSelectionMessage : public DofusMessage
{
public:
	uint16 id;

	uint32 GetOpcode() const
	{ return CMSG_SERVER_SELECTION; }

	ServerSelectionMessage(ByteBuffer& data)
	{
		data>>id;
	}
};

#endif