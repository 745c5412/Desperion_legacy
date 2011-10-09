#ifndef __SERVER_STATUS_UPDATE_MESSAGE__
#define __SERVER_STATUS_UPDATE_MESSAGE__

class ServerStatusUpdateMessage : public DofusMessage
{
public:
	uint32 GetOpcode() const
	{ return SMSG_SERVER_STATUS_UPDATE; }

	ServerStatusUpdateMessage(GameServerInformations infos)
	{
		m_buffer<<infos;
	}
};

#endif