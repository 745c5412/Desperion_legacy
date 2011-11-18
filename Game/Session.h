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

struct CommandHandler
{
	uint8 level;
	std::string description;
	std::string arguments;
	void (Session::*handler)(std::vector<std::string>&, bool);
	uint8 argc;
};

struct GamePacketHandler
{
	uint8 Flag;
	void (Session::*Handler)(ByteBuffer&);

	GamePacketHandler()
	{
		Flag = FLAG_CHARACTER;
	}
};

class Session : public AbstractSession<GamePacketHandler>
{
private:
	typedef std::tr1::unordered_map<std::string, CommandHandler> CommandStorageMap;
	static CommandStorageMap m_commands;
	AccountData m_data[FLAGS_NUMBER];
	time_t m_subscriptionEnd;
	Character* m_char;
	std::vector<int8> m_channels;
	std::vector<int8> m_disallowed;
	std::vector<int> m_friends;
	std::vector<int> m_ennemies;
	std::vector<int> m_ignored;
	uint32 m_lastNameSuggestionRequest;
	bool m_away;
	bool m_invisible;

	// AdminHandler.cpp
	void HandleAdminCommand(std::string&, bool);

	void HandleMoveToCommand(std::vector<std::string>&, bool);
	void HandleAddItemCommand(std::vector<std::string>&, bool);
	void HandleManCommand(std::vector<std::string>&, bool);
	void HandleAdminCommandMessage(ByteBuffer&);
	void HandleAdminQuietCommandMessage(ByteBuffer&);
	void HandleListCommand(std::vector<std::string>&, bool);
	void HandleNameAnnounceCommand(std::vector<std::string>&, bool);
	void HandleInfoMessageCommand(std::vector<std::string>&, bool);

	// CharacterHandler.cpp
	void SendCharacterSelectedSuccess(CharacterMinimals*);

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

	// ChatHandler.cpp
	void HandlePrivateMessage(ChatClientPrivateMessage*);
	void HandleMultiMessage(ChatClientMultiMessage*);

	void HandleChatClientMultiMessage(ByteBuffer&);
	void HandleChatClientMultiWithObjectMessage(ByteBuffer&);
	void HandleChatClientPrivateMessage(ByteBuffer&);
	void HandleChatClientPrivateWithObjectMessage(ByteBuffer&);
	void HandleChannelEnablingMessage(ByteBuffer&);

	// BasicHandler.cpp
	void HandleBasicPingMessage(ByteBuffer&);

	// InventoryHandler.cpp
	void HandleObjectDeleteMessage(ByteBuffer&);
	void HandleObjectDropMessage(ByteBuffer&);
	void HandleObjectSetPositionMessage(ByteBuffer&);
	void HandleLivingObjectChangeSkinRequestMessage(ByteBuffer&);
	void HandleLivingObjectDissociateMessage(ByteBuffer&);
	void HandleLivingObjectMessageRequestMessage(ByteBuffer&);
	void HandleObjectFeedMessage(ByteBuffer&);

	// Session.cpp
	void HandleAuthenticationTicketMessage(ByteBuffer&);
public:
	static void InitHandlersTable();
	static void InitCommandsTable();
	void Start();

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

	Session() : m_char(NULL), m_away(false), m_invisible(false)
	{
		m_data[FLAG_GUID].intValue = 0;
		m_lastNameSuggestionRequest = 0;
	}

	~Session();
	void Save();

	AccountData GetData(uint32 index) const
	{ return m_data[index]; }

	AccountData* GetAccount()
	{ return m_data; }

	time_t GetSubscriptionEnd() const
	{ return m_subscriptionEnd; }

	Character* GetCharacter() const
	{ return m_char; }

	bool IsAway() const
	{ return m_away; }

	bool IsInvisible() const
	{ return m_invisible; }

	void RemoveChannel(int8);
	bool HasChannel(int8);

	bool IsFriendWith(std::string);
	bool IsEnnemyWith(std::string);
	bool IsIgnoredWith(std::string);
};

#endif