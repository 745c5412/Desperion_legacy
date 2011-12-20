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

#ifndef __MASTER__
#define __MASTER__

namespace Desperion
{
	extern Database* sDatabase;
	extern Database* eDatabase;

	class Master : public Singleton<Master>
	{
	public:
		Master() : m_stopEvent(false), sListener(NULL)
		{
		}

		bool Run(int, char **);
		~Master();
		SocketListener<Session>* sListener;

		uint32 GetUpTime() const
		{ return getMSTime() - m_startTime; }

		void Stop()
		{
			m_service.stop();
			m_stopEvent = true;
		}

		boost::asio::io_service& GetService()
		{ return m_service; }
	private:
		bool StartUpDatabase();

		boost::asio::io_service m_service;
		uint32 m_startTime;
		bool m_stopEvent;
	};
}

#endif