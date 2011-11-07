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

class GameServer;

enum ReqFlag
{
	FLAG_NOT_CONNECTED,
	FLAG_CONNECTED,
	FLAG_OUT_OF_QUEUE,
};

enum AccountFlag
{
	FLAG_PSEUDO = 0,
	FLAG_GUID = 1,
	FLAG_LEVEL = 2,
	FLAG_QUESTION = 3,
	FLAG_ACCOUNT = 4,
	FLAG_LAST_SERVER = 5,
	FLAGS_NUMBER = 6,
};

struct AccountData
{
	std::string stringValue;
	int intValue;
	bool boolValue;
};

struct LoginPacketHandler
{
	uint8 Flag;
	void (Session::*Handler)(ByteBuffer&);

	LoginPacketHandler()
	{
		Flag = FLAG_OUT_OF_QUEUE;
	}
};

inline static bool VerifyVersion(Version& v)
{
	uint8 currentMajor = 2;
	uint8 currentMinor = 4;
	uint8 currentRelease = 6;
	uint16 currentRevision = 51301;
	uint8 currentPatch = 1;
	uint8 currentBuildType = 0;

	return v.major == currentMajor
		&& v.minor == currentMinor
		&& v.release == currentRelease
		&& v.rev == currentRevision
		&& v.patch == currentPatch
		&& v.buildType == currentBuildType;
}

inline static std::string GenerateRandomKey()
{
	std::string hash = "abcdefghijklmnopqrstuvwxyz";
	std::string result = "";
	size_t size = hash.size() - 1;
	for(uint8 a = 0; a < 32; ++a)
		result += hash[RandomUInt(size)];
	return result;
}

class Session : public BaseSession<LoginPacketHandler>
{
private:
	AccountData m_data[FLAGS_NUMBER];
	std::string m_key;
	time_t m_subscriptionEnd;

	void HandleIdentification(IdentificationMessage*);
	bool HandleServerSelection(GameServer*, bool);
	void SendServersList();

	void HandleIdentificationMessage(ByteBuffer&);
	void HandleIdentificationWithServerIdMessage(ByteBuffer&);
	void HandleServerSelectionMessage(ByteBuffer&);
	void HandleAcquaintanceSearchMessage(ByteBuffer&);
public:
	static void InitHandlersTable();
	void Start();

	void OnData(LoginPacketHandler* hdl, ByteBuffer& packet)
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
		}
		return true;
	}

	bool CanSelect(uint8 state)
	{
		switch(state)
		{
		case OFFLINE:
		case STARTING:
		case STATUS_UNKNOWN:
		case SAVING:
		case STOPING:
			return false;
		case ONLINE:
			return true;
		case NOJOIN:
			return m_data[FLAG_LEVEL].intValue > 0;
		case FULL:
			return IsSubscriber();
		default:
			return false;
		}
	}

	Session()
	{
		m_data[FLAG_GUID].intValue = 0;
	}

	~Session();

	AccountData GetData(uint32 index) const
	{ return m_data[index]; }

	AccountData* GetAccount()
	{ return m_data; }

	time_t GetSubscriptionEnd() const
	{ return m_subscriptionEnd; }

	GameServerInformations GetServerStatusMessage(const GameServer*, uint8);
};

#endif