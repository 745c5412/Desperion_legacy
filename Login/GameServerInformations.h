#ifndef __GAME_SERVER_INFORMATIONS__
#define __GAME_SERVER_INFORMATIONS__

class GameServerInformations : public DofusModel
{
public:
	uint32 GetProtocol() const
	{ return GAME_SERVER_INFORMATIONS; }

	GameServerInformations(int16 id, int8 status, int8 completion, bool isSelectable, int8 charactersCount, uint64 date)
	{
		m_buffer<<id<<status<<completion<<isSelectable<<charactersCount<<date;
	}
};

#endif