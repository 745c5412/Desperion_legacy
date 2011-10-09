#ifndef __SELECTED_SERVER_DATA_MESSAGE__
#define __SELECTED_SERVER_DATA_MESSAGE__

class SelectedServerDataMessage : public DofusMessage
{
public:
	uint32 GetOpcode() const
	{ return SMSG_SELECTED_SERVER_DATA; }

	SelectedServerDataMessage(uint16 id, std::string ip, uint16 port, bool canCreateNewCharacter, std::string& ticket)
	{
		m_buffer<<id<<ip<<port<<canCreateNewCharacter<<ticket;
	}
};

#endif