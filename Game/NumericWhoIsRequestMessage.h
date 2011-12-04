#ifndef __NUMERIC_WHO_IS_REQUEST_MESSAGE__
#define __NUMERIC_WHO_IS_REQUEST_MESSAGE__

class NumericWhoIsRequestMessage : public DofusMessage
{
public:
	int playerId;

	virtual uint16 GetOpcode() const
	{ return CMSG_NUMERIC_WHO_IS_REQUEST; }

	NumericWhoIsRequestMessage()
	{
	}

	NumericWhoIsRequestMessage(int playerId) : playerId(playerId)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<playerId;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>playerId;
	}
};

#endif