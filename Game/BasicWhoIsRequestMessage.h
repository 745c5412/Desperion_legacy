#ifndef __BASIC_WHO_IS_REQUEST_MESSAGE__
#define __BASIC_WHO_IS_REQUEST_MESSAGE__

class BasicWhoIsRequestMessage : public DofusMessage
{
public:
	std::string search;

	virtual uint16 GetOpcode() const
	{ return CMSG_BASIC_WHO_IS_REQUEST; }

	BasicWhoIsRequestMessage()
	{
	}

	BasicWhoIsRequestMessage(std::string search) : search(search)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data>>search;
	}

	void Deserialize(ByteBuffer& data)
	{
		data<<search;
	}
};

#endif