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

inline static bool VerifyVersion(VersionPtr v)
{
	return v->major == DOFUS_VERSION_MAJOR
		&& v->minor == DOFUS_VERSION_MINOR
		&& v->release == DOFUS_VERSION_RELEASE
		&& v->revision == DOFUS_VERSION_REVISION
		&& v->patch == DOFUS_VERSION_PATCH
		&& v->buildType == DOFUS_VERSION_BUILD_TYPE;
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

class Session : public AbstractSession<LoginPacketHandler>
{
	friend class DofusQueue;
private:
	AccountData m_data[FLAGS_NUMBER];
	std::string m_salt;
	time_t m_subscriptionEnd;
	std::ofstream m_logs;
	boost::shared_ptr<boost::asio::deadline_timer> m_idleTimer, m_queueTimer;
	bool m_isInQueue;
	int m_counter;
	int m_queueSize;

	void HandleIdentification(boost::shared_ptr<IdentificationMessage>);
	bool HandleServerSelection(GameServer*, bool);
	void SendServersList();
	void SendQueueStatus();

	void HandleIdentificationMessage(ByteBuffer&);
	void HandleServerSelectionMessage(ByteBuffer&);
	void HandleAcquaintanceSearchMessage(ByteBuffer&);
public:
	static void InitHandlersTable();
	void Start();
	void LOG(const char*, ...);

	void HandleData(LoginPacketHandler* hdl, ByteBuffer& packet)
	{
		UpdateIdleTimer();
		(this->*hdl->Handler)(packet);
	}
	
	void UpdateIdleTimer()
	{
		m_idleTimer = ThreadPool::Instance().TimedSchedule(boost::bind(&Session::CloseSocket, this),
			boost::posix_time::minutes(Config::Instance().GetParam(MAX_IDLE_TIME_STRING,
			MAX_IDLE_TIME_DEFAULT)));
	}

	bool IsSubscriber() const
	{ return m_subscriptionEnd > time(NULL); }

	bool IsAllowed(uint8 flag)
	{
		switch(flag)
		{
		case FLAG_NOT_CONNECTED:
			return m_data[FLAG_GUID].intValue == 0;
		case FLAG_CONNECTED:
			return m_data[FLAG_GUID].intValue != 0;
		case FLAG_OUT_OF_QUEUE:
			return !m_isInQueue;
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

	Session(boost::asio::io_service& ios) : AbstractSession<LoginPacketHandler>(ios),
		m_isInQueue(true), m_counter(0), m_queueSize(0)
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

	GameServerInformations* GetServerStatusMessage(const GameServer*, uint8);
};

class DofusQueue : public Singleton<DofusQueue>
{
private:
	tbb::concurrent_queue<std::pair<boost::weak_ptr<Session>, boost::shared_ptr<IdentificationMessage> > >
		m_queue;
	tbb::atomic<int> m_counter;

public:
	DofusQueue()
	{
		m_counter = 0;
	}

	int Push(std::pair<boost::weak_ptr<Session>, boost::shared_ptr<IdentificationMessage> >& p, int& size)
	{
		bool empty = m_queue.empty();
		m_queue.push(p);
		if(empty)
			ThreadPool::Instance().GetService().post(boost::bind(&DofusQueue::Next, this));
		size = m_queue.unsafe_size();
		return m_counter;
	}

	int GetCounter() const
	{ return m_counter; }

	int GetSize() const
	{ return m_queue.unsafe_size(); }

	void Next()
	{
		std::pair<boost::weak_ptr<Session>, boost::shared_ptr<IdentificationMessage> > p;
		while(true)
		{
			if(m_queue.empty())
				break;
			if(!m_queue.try_pop(p))
				continue;
			++m_counter;
			try
			{
				boost::shared_ptr<Session> S(p.first);
				S->HandleIdentification(p.second);
			}catch(const boost::bad_weak_ptr&) { continue; }
			catch(...) { }
			break;
		}
	}
};

#endif