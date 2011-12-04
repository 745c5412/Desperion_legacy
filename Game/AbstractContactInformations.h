#ifndef __ABSTRACT_CONTACT_INFORMATIONS__
#define __ABSTRACT_CONTACT_INFORMATIONS__

class AbstractContactInformations : public DofusModel
{
public:
	int accountId;
	std::string accountName;

	virtual uint16 GetProtocol() const
	{ return ABSTRACT_CONTACT_INFORMATIONS; }

	AbstractContactInformations()
	{
	}

	AbstractContactInformations(int accountId, std::string accountName) : accountId(accountId),
		accountName(accountName)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<accountId<<accountName;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>accountId>>accountName;
	}
};

#endif