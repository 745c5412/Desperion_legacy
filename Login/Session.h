#ifndef __SESSION__
#define __SESSION__

class GameServer;

enum ServerConnectionError
{
	SERVER_CONNECTION_ERROR_DUE_TO_STATUS = 0,
	SERVER_CONNECTION_ERROR_NO_REASON = 1,
	SERVER_CONNECTION_ERROR_ACCOUNT_RESTRICTED = 2,
	SERVER_CONNECTION_ERROR_COMMUNITY_RESTRICTED = 3,
	SERVER_CONNECTION_ERROR_LOCATION_RESTRICTED = 4,
	SERVER_CONNECTION_ERROR_SUBSCRIBERS_ONLY = 5,
	SERVER_CONNECTION_ERROR_REGULAR_PLAYERS_ONLY = 6,
};

enum ServerStatus
{
	STATUS_UNKNOWN = 0,
	OFFLINE = 1,
	STARTING = 2,
	ONLINE = 3,
	NOJOIN = 4,
	SAVING = 5,
	STOPING = 6,
	FULL = 7,
};

enum IdentificationFailureReason
{
	BAD_VERSION = 1,
	WRONG_CREDENTIALS = 2,
	BANNED = 3,
	KICKED = 4,
	IN_MAINTENANCE = 5,
	TOO_MANY_ON_IP = 6,
	TIME_OUT = 7,
	BAD_IPRANGE = 8,
	CREDENTIALS_RESET = 9,
	UNKNOWN_AUTH_ERROR = 99,
	SPARE = 100,
};

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
	FLAGS_NUMBER = 5,
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
	uint8 currentRelease = 1;
	uint16 currentRevision = 50166;
	uint8 currentPatch = 2;
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

	void HandleIdentificationMessage(ByteBuffer&);
	void HandleServerSelectionMessage(ByteBuffer&);
	void HandleAcquaintanceSearchMessage(ByteBuffer&);
public:
	static void InitHandlersTable();
	void Start();

	void OnData(LoginPacketHandler* hdl, ByteBuffer& packet)
	{ (this->*hdl->Handler)(packet); }

	bool IsSubscriber()
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
		World::Instance().AddSession(this);
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