#ifndef __BASIC_WHO_IS_NO_MATCH_MESSAGE__
#define __BASIC_WHO_IS_NO_MATCH_MESSAGE__

class BasicWhoIsNoMatchMessage : public DofusMessage
{
public:
	std::string search;

	virtual uint16 GetOpcode() const
	{ return SMSG_BASIC_WHO_IS_NO_MATCH; }

	BasicWhoIsNoMatchMessage()
	{
	}

	BasicWhoIsNoMatchMessage(std::string search) : search(search)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<search;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>search;
	}
};

#endif