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

#include "StdAfx.h"

template<> ThreadPool* Singleton<ThreadPool>::m_singleton = NULL;

void ThreadPool::BasicWorker()
{
	try{
	m_service.run();
	}catch(const std::exception& e)
	{
		Log::Instance().outError("UNHANDLED EXCEPTION: %s", e.what());
	}
}

ThreadPool::ThreadPool() : m_work(m_service)
{
	SpawnWorkerThreads();
}

ThreadPool::~ThreadPool()
{
	ClearWorkerThreads();
}

void ThreadPool::SpawnWorkerThreads()
{
	uint32 count = boost::thread::hardware_concurrency();
	if(count == 0)
		count = 2;
	for(uint32 a = 0; a < count; ++a)
		m_threads.push_back(new boost::thread(boost::bind(&ThreadPool::BasicWorker, this)));
}

void ThreadPool::ClearWorkerThreads()
{
	if(!m_service.stopped())
		m_service.stop();
	m_service.reset();
	for(std::list<boost::thread*>::iterator it = m_threads.begin(); it != m_threads.end(); ++it)
	{
		(*it)->interrupt();
		delete *it;
	}
}