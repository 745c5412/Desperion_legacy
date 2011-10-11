/*
	This file is part of Desperion.
	Copyright 2010, 2011 LittleScaraby, Nekkro

    Desperion is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Desperion is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Desperion.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __SESSION__
#define __SESSION__

enum ReqFlag
{
	FLAG_NOT_CONNECTED,
	FLAG_CONNECTED,
	FLAG_OUT_OF_QUEUE,
	FLAG_CHARACTER,
};

enum AccountFlag
{
	FLAG_PSEUDO = 0,
	FLAG_GUID = 1,
	FLAG_LEVEL = 2,
	FLAG_ANSWER = 3,
	FLAG_ACCOUNT = 4,
	FLAG_LANG = 5,
	FLAG_LAST_CONN = 6,
	FLAG_LAST_IP = 7,
	FLAGS_NUMBER = 8,
};

struct AccountData
{
	std::string stringValue;
	int intValue;
	bool boolValue;
};

class Session;

struct GamePacketHandler
{
	uint8 Flag;
	void (Session::*Handler)(ByteBuffer&);

	GamePacketHandler()
	{
		Flag = FLAG_CHARACTER;
	}
};

class Session : public BaseSession<GamePacketHandler>
{
private:
	AccountData m_data[FLAGS_NUMBER];
	time_t m_subscriptionEnd;
	Character* m_char;
	std::vector<uint32> m_channels;
	std::vector<uint32> m_disallowed;
	std::vector<uint32> m_friends;
	std::vector<uint32> m_ennemies;
	std::vector<uint32> m_ignored;
	uint32 m_lastNameSuggestionRequest;

	// CharacterHandler.cpp
	void HandleCharactersListRequestMessage(ByteBuffer&);
	void HandleCharacterDeletionRequestMessage(ByteBuffer&);
	void HandleCharacterNameSuggestionRequestMessage(ByteBuffer&);
	void HandleCharacterSelectionMessage(ByteBuffer&);
	void HandleCharacterCreationRequestMessage(ByteBuffer&);

	// ContextHandler.cpp
	void HandleGameContextCreateRequestMessage(ByteBuffer&);
	void HandleMapInformationsRequestMessage(ByteBuffer&);
	void HandleGameMapMovementRequestMessage(ByteBuffer&);
	void HandleGameMapMovementConfirmMessage(ByteBuffer&);
	void HandleChangeMapMessage(ByteBuffer&);

	// Session.cpp
	void HandleAuthenticationTicketMessage(ByteBuffer&);
	void HandleAdminCommandMessage(ByteBuffer&);
	void HandleAdminQuietCommandMessage(ByteBuffer&);
public:
	static void InitHandlersTable();
	void Start();
	void SendToMap(const DofusMessage&, bool self = true);

	void OnData(GamePacketHandler* hdl, ByteBuffer& packet)
	{ (this->*hdl->Handler)(packet); }

	bool IsSubscriber() const
	{ return true; }

	bool IsAllowed(uint8 flag)
	{
		switch(flag)
		{
		case FLAG_NOT_CONNECTED:
			return m_data[FLAG_GUID].intValue == 0;
		case FLAG_CONNECTED:
			return m_data[FLAG_GUID].intValue != 0;
		case FLAG_OUT_OF_QUEUE:
			return true; // todo
		case FLAG_CHARACTER:
			return m_char != NULL;
		}
		return true;
	}

	Session()
	{
		m_char = NULL;
		m_data[FLAG_GUID].intValue = 0;
		m_lastNameSuggestionRequest = 0;
		World::Instance().AddSession(this);
	}

	~Session();

	AccountData GetData(uint32 index) const
	{ return m_data[index]; }

	AccountData* GetAccount()
	{ return m_data; }

	time_t GetSubscriptionEnd() const
	{ return m_subscriptionEnd; }

	Character* GetCharacter() const
	{ return m_char; }
};

#endif