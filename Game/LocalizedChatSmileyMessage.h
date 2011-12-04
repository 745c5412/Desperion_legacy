#ifndef __LOCALIZED_CHAT_SMILEY_MESSAGE__
#define __LOCALIZED_CHAT_SMILEY_MESSAGE__

class LocalizedChatSmileyMessage : public ChatSmileyMessage
{
public:
	int16 cellId;

	virtual uint16 GetOpcode() const
	{ return SMSG_LOCALIZED_CHAT_SMILEY; }

	LocalizedChatSmileyMessage()
	{
	}

	LocalizedChatSmileyMessage(int entityId, int8 smileyId, int accountId, int16 cellId)
		: ChatSmileyMessage(entityId, smileyId, accountId), cellId(cellId)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		ChatSmileyMessage::Serialize(data);
		data<<cellId;
	}

	void Deserialize(ByteBuffer& data)
	{
		ChatSmileyMessage::Deserialize(data);
		data>>cellId;
	}
};

#endif