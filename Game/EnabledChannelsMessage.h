#ifndef __ENABLED_CHANNELS_MESSAGE__
#define __ENABLED_CHANNELS_MESSAGE__

class EnabledChannelsMessage : public DofusMessage
{
public:
	std::vector<int8> channels, disallowed;

	virtual uint16 GetOpcode() const
	{ return SMSG_ENABLED_CHANNELS; }

	EnabledChannelsMessage()
	{
	}

	EnabledChannelsMessage(std::vector<int8>& channels, std::vector<int8>& disallowed) : channels(channels),
		disallowed(disallowed)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		uint16 size = channels.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<channels[a];
		size = disallowed.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<disallowed[a];
	}

	void Deserialize(ByteBuffer& data)
	{
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int8 chann;
			data>>chann;
			channels.push_back(chann);
		}
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int8 dis;
			data>>dis;
			disallowed.push_back(dis);
		}
	}
};

#endif