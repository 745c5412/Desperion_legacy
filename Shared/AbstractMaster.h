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

#ifndef __ABSTRACT_MASTER__
#define __ABSTRACT_MASTER__

#ifndef _WIN32
void OnCrash();
#endif
void SignalShutDown(); // effectuer un shutdown depuis le gestionnaire de signaux

enum ShutDownType
{
	SHUTDOWN_NOT_REQUESTED,
	SHUTDOWN_NORMAL,
	SHUTDOWN_REBOOT,
};

class AbstractMaster
{
public:
	AbstractMaster() : m_work(new boost::asio::io_service::work(m_service)),
		m_startTime(getMSTime())
	{
	}

	virtual ShutDownType Run(int, char **) = 0;
			
	uint32 GetUpTime() const
	{ return getMSTime() - m_startTime; }

	boost::asio::io_service& GetService()
	{ return m_service; }

	void ShutDown(ShutDownType s)
	{
		m_shutdown = s;
		delete m_work;
	}

protected:
	volatile ShutDownType m_shutdown;
	boost::asio::io_service m_service;
	virtual bool StartUpDatabase() = 0;

private:
	uint32 m_startTime;
	boost::asio::io_service::work* m_work;
};

inline void OnSignal(int s)
{
	switch (s)
	{
	case SIGINT:
	case SIGTERM:
	case SIGABRT:
#ifdef _WIN32
	case SIGBREAK:
#endif
		SignalShutDown();
		break;
	}
	signal(s, OnSignal);
}

inline void HookSignals()
{
	signal(SIGINT, OnSignal);
	signal(SIGTERM, OnSignal);
	signal(SIGABRT, OnSignal);
#ifdef _WIN32
	signal(SIGBREAK, OnSignal);
#else
	signal(SIGSEGV, ::OnCrash);
	signal(SIGFPE, ::OnCrash);
	signal(SIGILL, ::OnCrash);
	signal(SIGBUS, ::OnCrash);
#endif
}

inline void UnHookSignals()
{
	signal(SIGINT, 0);
	signal(SIGTERM, 0);
	signal(SIGABRT, 0);
#ifdef _WIN32
	signal(SIGBREAK, 0);
#else
	signal(SIGSEGV, 0);
	signal(SIGFPE, 0);
	signal(SIGILL, 0);
	signal(SIGBUS, 0);
#endif
}

#endif