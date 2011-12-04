#ifndef __CHAT_SMILEY_MESSAGE__
#define __CHAT_SMILEY_MESSAGE__

class ChatSmileyMessage : public DofusMessage
{
public:
	int entityId, accountId;
	int8 smileyId;

	virtual uint16 GetOpcode() const
	{ return SMSG_CHAT_SMILEY; }

	ChatSmileyMessage()
	{
	}

	ChatSmileyMessage(int entityId, int8 smileyId, int accountId) : entityId(entityId),
		smileyId(smileyId), accountId(accountId)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<entityId<<smileyId<<accountId;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>entityId>>smileyId>>accountId;
	}
};

#endif