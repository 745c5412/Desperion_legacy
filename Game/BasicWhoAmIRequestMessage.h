#ifndef __BASIC_WHO_AM_I_REQUEST_MESSAGE__
#define __BASIC_WHO_AM_I_REQUEST_MESSAGE__

class BasicWhoAmIRequestMessage : public DofusMessage
{
public:
	virtual uint16 GetOpcode() const
	{ return CMSG_BASIC_WHO_AM_I_REQUEST; }

	BasicWhoAmIRequestMessage()
	{
	}

	void Serialize(ByteBuffer& data)
	{
	}

	void Deserialize(ByteBuffer& data)
	{
	}
};

#endif