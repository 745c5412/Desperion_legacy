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

#ifndef __THREAD_POOL__
#define __THREAD_POOL__

class ThreadPool : public Singleton<ThreadPool>
{
private:
	std::list<boost::thread*> m_threads;
	boost::asio::io_service m_service;
	boost::asio::io_service::work m_work;

	void TimedScheduleCallback(boost::function<void()> task, boost::shared_ptr<boost::asio::deadline_timer> timer,
		const boost::system::error_code& error)
	{
		if(error)
			return;
		Schedule(task);
	}

	void PeriodicScheduleCallback(boost::function<void()> task, boost::shared_ptr<boost::asio::deadline_timer> timer,
		const boost::asio::deadline_timer::duration_type& delay, const boost::system::error_code& error)
	{
		if(error)
			return;
		Schedule(task);
		timer->expires_from_now(delay);
		timer->async_wait(boost::bind(&ThreadPool::PeriodicScheduleCallback, this, task, timer, delay,
			boost::asio::placeholders::error));
	}

public:
	ThreadPool();
	virtual ~ThreadPool();
	void SpawnWorkerThreads();
	void ClearWorkerThreads();
	void BasicWorker();

	boost::asio::io_service& GetIoService()
	{ return m_service; }

	void Schedule(boost::function<void()> task)
	{ m_service.post(task); }

	boost::shared_ptr<boost::asio::deadline_timer>
	TimedSchedule(boost::function<void()> task, const boost::asio::deadline_timer::duration_type& delay)
	{
		boost::shared_ptr<boost::asio::deadline_timer> timer(new boost::asio::deadline_timer(m_service, delay));
		timer->async_wait(boost::bind(&ThreadPool::TimedScheduleCallback, this, task, timer,
			boost::asio::placeholders::error));
		return timer;
	}

	boost::shared_ptr<boost::asio::deadline_timer> PeriodicSchedule(boost::function<void()> task,
		const boost::asio::deadline_timer::duration_type& delay)
	{
		Schedule(task);
		boost::shared_ptr<boost::asio::deadline_timer> timer(new boost::asio::deadline_timer(m_service, delay));
		timer->async_wait(boost::bind(&ThreadPool::PeriodicScheduleCallback, this, task, timer, delay,
			boost::asio::placeholders::error));
		return timer;
	}

	boost::shared_ptr<boost::asio::deadline_timer> TimedPeriodicSchedule(boost::function<void()> task,
		const boost::asio::deadline_timer::duration_type& initial, const boost::asio::deadline_timer::duration_type& delay)
	{
		boost::shared_ptr<boost::asio::deadline_timer> timer(new boost::asio::deadline_timer(m_service, initial));
		timer->async_wait(boost::bind(&ThreadPool::PeriodicScheduleCallback, this, task, timer, delay,
			boost::asio::placeholders::error));
		return timer;
	}
};

#endif