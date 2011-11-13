#ifndef __BASIC_TIME_MESSAGE__
#define __BASIC_TIME_MESSAGE__

class BasicTimeMessage : public DofusMessage
{
public:
	int timestamp;
	int16 offset;

	virtual uint16 GetOpcode() const
	{ return SMSG_BASIC_TIME; }

	BasicTimeMessage()
	{
	}

	BasicTimeMessage(int timestamp, int16 offset) : timestamp(timestamp), offset(offset)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<timestamp<<offset;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>timestamp>>offset;
	}
};

#endif