#ifndef __CHANNEL_ENABLING_MESSAGE__
#define __CHANNEL_ENABLING_MESSAGE__

class ChannelEnablingMessage : public DofusMessage
{
public:
	int8 channel;
	bool enable;

	virtual uint16 GetOpcode() const
	{ return CMSG_CHANNEL_ENABLING; }

	ChannelEnablingMessage()
	{
	}

	ChannelEnablingMessage(int8 channel, bool enable) : channel(channel), enable(enable)
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