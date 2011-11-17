#ifndef __MOOD_SMILEY_RESULT_MESSAGE__
#define __MOOD_SMILEY_RESULT_MESSAGE__

class MoodSmileyResultMessage : public DofusMessage
{
public:
	int8 resultCode, smileyId;

	virtual uint16 GetOpcode() const
	{ return SMSG_MOOD_SMILEY_RESULT; }

	MoodSmileyResultMessage()
	{
	}

	MoodSmileyResultMessage(int8 resultCode, int8 smileyId) : resultCode(resultCode), smileyId(smileyId)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<resultCode<<smileyId;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>resultCode>>smileyId;
	}
};

#endif