#ifndef __TRUST_STATUS_MESSAGE__
#define __TRUST_STATUS_MESSAGE__

class TrustStatusMessage : public DofusMessage
{
public:
	bool trusted;

	virtual uint16 GetOpcode() const
	{ return SMSG_TRUST_STATUS; }

	TrustStatusMessage()
	{
	}

	TrustStatusMessage(bool trusted) : trusted(trusted)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<trusted;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>trusted;
	}
};

#endif