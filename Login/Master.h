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

	class Master : public Singleton<Master>
	{
	public:
		Master()
		{
		}

		bool Run(int, char **);
		~Master();
		SocketListener<Session>* sListener;
		SocketListener<GameSession>* eListener;

		uint32 GetUpTime() const
		{ return getMSTime() - m_startTime; }

		boost::asio::io_service& GetService()
		{ return m_service; }

		void Stop()
		{ m_service.stop(); }

	private:
		bool StartUpDatabase();

		boost::asio::io_service m_service;
		uint32 m_startTime;
	};
};

#endif