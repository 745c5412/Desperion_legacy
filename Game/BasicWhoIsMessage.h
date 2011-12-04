#ifndef __BASIC_WHO_IS_MESSAGE__
#define __BASIC_WHO_IS_MESSAGE__

class BasicWhoIsMessage : public DofusMessage
{
public:
	bool self;
	uint8 position;
	std::string accountNickname, characterName;
	int16 areaId;

	virtual uint16 GetOpcode() const
	{ return SMSG_BASIC_WHO_IS; }

	BasicWhoIsMessage()
	{
	}

	BasicWhoIsMessage(bool self, uint8 position, std::string accountNickname, std::string characterName, int16 areaId)
		: self(self), position(position), accountNickname(accountNickname), characterName(characterName), areaId(areaId)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<self<<position<<accountNickname<<characterName<<areaId;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>self>>position>>accountNickname>>characterName>>areaId;
	}
};

#endif