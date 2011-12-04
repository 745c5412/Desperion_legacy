#ifndef __CHAT_SMILEY_REQUEST_MESSAGE__
#define __CHAT_SMILEY_REQUEST_MESSAGE__

class ChatSmileyRequestMessage : public DofusMessage
{
public:
	int8 smileyId;

	virtual uint16 GetOpcode() const
	{ return CMSG_CHAT_SMILEY_REQUEST; }

	ChatSmileyRequestMessage()
	{
	}

	ChatSmileyRequestMessage(int8 smileyId) : smileyId(smileyId)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<smileyId;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>smileyId;
	}
};

#endif