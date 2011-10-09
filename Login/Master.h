#ifndef __MASTER__
#define __MASTER__

namespace Desperion
{
	extern Database* sDatabase;

	class Master : public Singleton<Master>
	{
	public:
		Master() : m_version("1.1.0")
		{
		}

		bool Run(int, char **);
		~Master();
		SocketListener<Session>* sListener;
		SocketListener<GameSession>* eListener;

		uint32 GetUpTime() const
		{ return getMSTime() - m_startTime; }
		void Stop()
		{ m_running = false; }

	private:
		bool StartUpDatabase();

		bool m_running;
		uint32 m_startTime;
		std::string m_version;
	};
};

#endif