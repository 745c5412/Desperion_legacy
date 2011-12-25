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
	FLAG_PSEUDO,
	FLAG_GUID,
	FLAG_LEVEL,
	FLAG_ANSWER,
	FLAG_ACCOUNT,
	FLAG_LANG,
	FLAG_LAST_CONN,
	FLAG_LAST_IP,
	FLAGS_NUMBER,
};

enum BooleanValue
{
	BOOL_FRIEND_WARN_ON_CONNECTION,
	BOOL_FRIEND_WARN_ON_LEVEL_GAIN,
	BOOL_GUILD_MEMBER_WARN_ON_CONNECTION,
	BOOL_INVISIBLE,
	BOOL_AWAY,
	BOOL_OCCUPED,
	BOOLS_NUMBER,
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
	bool m_booleanValues[BOOLS_NUMBER];
	time_t m_subscriptionEnd;
	Character* m_char;
	std::set<int8> m_channels;
	std::set<int8> m_disallowed;
	boost::bimap<int, std::string> m_friends;
	boost::bimap<int, std::string> m_ennemies;
	boost::bimap<int, std::string> m_ignored;
	uint32 m_lastNameSuggestionRequest;
	std::ofstream m_logs;

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
	void HandleMoodSmileyRequestMessage(ByteBuffer&);
	void HandleChatSmileyRequestMessage(ByteBuffer&);

	// BasicHandler.cpp
	void HandleBasicPingMessage(ByteBuffer&);
	void HandleNumericWhoIsRequestMessage(ByteBuffer&);
	void HandleBasicWhoIsRequestMessage(ByteBuffer&);
	void HandleBasicWhoAmIRequestMessage(ByteBuffer&);

	// InventoryHandler.cpp
	void HandleObjectDeleteMessage(ByteBuffer&);
	void HandleObjectDropMessage(ByteBuffer&);
	void HandleObjectSetPositionMessage(ByteBuffer&);
	void HandleLivingObjectChangeSkinRequestMessage(ByteBuffer&);
	void HandleLivingObjectDissociateMessage(ByteBuffer&);
	void HandleLivingObjectMessageRequestMessage(ByteBuffer&);
	void HandleObjectFeedMessage(ByteBuffer&);

	// SocialHandler.cpp
	void HandleFriendsGetListMessage(ByteBuffer&);

	// Session.cpp
	void HandleAuthenticationTicketMessage(ByteBuffer&);
public:
	static void InitHandlersTable();
	static void InitCommandsTable();
	void Start();
	void LOG(const char*, ...);
	CharacterStatsListMessage GetCharacterStatsListMessage();

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

	Session() : m_char(NULL)
	{
		m_data[FLAG_GUID].intValue = 0;
		m_lastNameSuggestionRequest = 0;
		m_booleanValues[BOOL_INVISIBLE] = false;
		m_booleanValues[BOOL_AWAY] = false;
	}

	~Session();
	void Save();

	AccountData GetData(AccountFlag index) const
	{ return m_data[index]; }

	AccountData* GetAccount()
	{ return m_data; }

	time_t GetSubscriptionEnd() const
	{ return m_subscriptionEnd; }

	Character* GetCharacter() const
	{ return m_char; }

	bool GetBoolValue(BooleanValue index)
	{ return m_booleanValues[index]; }

	void SetBoolValue(BooleanValue index, bool value)
	{ m_booleanValues[index] = value; }

	void RemoveChannel(int8);

	bool IsFriendWith(int id)
	{ return m_friends.left.find(id) != m_friends.left.end(); }

	bool IsFriendWith(std::string name)
	{ return m_friends.right.find(Desperion::ToLowerCase(name)) != m_friends.right.end(); }

	bool IsEnnemyWith(int id)
	{ return m_ennemies.left.find(id) != m_ennemies.left.end(); }

	bool IsEnnemyWith(std::string name)
	{ return m_ennemies.right.find(Desperion::ToLowerCase(name)) != m_ennemies.right.end(); }

	bool IsIgnoredWith(int id)
	{ return m_ignored.left.find(id) != m_ignored.left.end(); }

	bool IsIgnoredWith(std::string name)
	{ return m_ignored.right.find(Desperion::ToLowerCase(name)) != m_ignored.right.end(); }

	bool HasChannel(int8 chann)
	{ return m_channels.find(chann) != m_channels.end(); }
};

#endif