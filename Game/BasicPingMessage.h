#ifndef __BASIC_PING_MESSAGE__
#define __BASIC_PING_MESSAGE__

class BasicPingMessage : public DofusMessage
{
public:
	bool quiet;

	virtual uint32 GetOpcode() const
	{ return CMSG_BASIC_PING; }

	BasicPingMessage(ByteBuffer& data)
	{
		data>>quiet;
	}
};

#endif