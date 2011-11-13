#ifndef __BASIC_PING_MESSAGE__
#define __BASIC_PING_MESSAGE__

class BasicPingMessage : public DofusMessage
{
public:
	bool quiet;

	virtual uint16 GetOpcode() const
	{ return CMSG_BASIC_PING; }

	BasicPingMessage()
	{
	}

	BasicPingMessage(bool quiet) : quiet(quiet)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<quiet;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>quiet;
	}
};

#endif