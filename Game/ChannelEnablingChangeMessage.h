#ifndef __CHANNEL_ENABLING_CHANGE_MESSAGE__
#define __CHANNEL_ENABLING_CHANGE_MESSAGE__

class ChannelEnablingChangeMessage : public DofusMessage
{
public:
	int8 channel;
	bool enable;

	virtual uint16 GetOpcode() const
	{ return SMSG_CHANNEL_ENABLING_CHANGE; }

	ChannelEnablingChangeMessage()
	{
	}

	ChannelEnablingChangeMessage(int8 channel, bool enable) : channel(channel), enable(enable)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<channel<<enable;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>channel>>enable;
	}
};

#endif