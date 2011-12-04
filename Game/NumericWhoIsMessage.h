#ifndef __NUMERIC_WHO_IS_MESSAGE__
#define __NUMERIC_WHO_IS_MESSAGE__

class NumericWhoIsMessage : public DofusMessage
{
public:
	int playerId, accountId;

	virtual uint16 GetOpcode() const
	{ return SMSG_NUMERIC_WHO_IS; }

	NumericWhoIsMessage()
	{
	}

	NumericWhoIsMessage(int playerId, int accountId) : playerId(playerId), accountId(accountId)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<playerId<<accountId;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>playerId>>accountId;
	}
};

#endif