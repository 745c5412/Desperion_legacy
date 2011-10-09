#ifndef __ACQUAINTANCE_SERVER_LIST_MESSAGE__
#define __ACQUAINTANCE_SERVER_LIST_MESSAGE__

class AcquaintanceServerListMessage : public DofusMessage
{
public:
	uint32 GetOpcode() const
	{ return SMSG_ACQUAINTANCE_SERVER_LIST; }

	AcquaintanceServerListMessage(std::vector<int16>& servers)
	{
		uint16 size = servers.size();
		m_buffer<<size;
		for(uint16 a = 0; a < size; ++a)
			m_buffer<<servers[a];
	}
};

#endif