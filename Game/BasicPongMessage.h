#ifndef __BASIC_PONG_MESSAGE__
#define __BASIC_PONG_MESSAGE__

class BasicPongMessage : public DofusMessage
{
public:
	bool quiet;

	virtual uint16 GetOpcode() const
	{ return SMSG_BASIC_PONG; }

	BasicPongMessage()
	{
	}

	BasicPongMessage(bool quiet) : quiet(quiet)
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