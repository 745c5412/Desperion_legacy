#ifndef __SERVERS_LIST_MESSAGE__
#define __SERVERS_LIST_MESSAGE__

class ServersListMessage : public DofusMessage
{
public:
	uint32 GetOpcode() const
	{ return SMSG_SERVERS_LIST; }

	ServersListMessage(std::vector<GameServerInformations>& servers)
	{
		uint16 size = servers.size();
		m_buffer<<size;
		for(uint16 a = 0; a < size; ++a)
			m_buffer<<servers[a];
	}
};

#endif