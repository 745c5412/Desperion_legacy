#ifndef __MOOD_SMILEY_REQUEST_MESSAGE__
#define __MOOD_SMILEY_REQUEST_MESSAGE__

class MoodSmileyRequestMessage : public DofusMessage
{
public:
	int8 smileyId;

	virtual uint16 GetOpcode() const
	{ return CMSG_MOOD_SMILEY_REQUEST; }

	MoodSmileyRequestMessage()
	{
	}

	MoodSmileyRequestMessage(int8 smileyId) : smileyId(smileyId)
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