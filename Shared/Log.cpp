/*
	This file is part of Desperion.
	Copyright 2010, 2011 LittleScaraby

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

template <> Log * Singleton <Log>::m_singleton = NULL;

#ifndef WIN32
static const char* colorstrings[TBLUE+1] = {
"",
"\033[22;31m",
"\033[22;32m",
"\033[01;33m",
//"\033[22;37m",
"\033[0m",
"\033[01;37m",
"\033[22;34m",
};
#endif

void Log::outColor(uint32 colorcode, const char * str, ...)
{
	if(!str) 
		return;

	va_list ap;
	char buf[32768];
	va_start(ap, str);
	vsnprintf(buf, 32768, str, ap);
	va_end(ap);

	if(m_flags & OUT_STRING)
	{
		m_lock.lock();
#ifdef WIN32
		SetConsoleTextAttribute(stdout_handle, colorcode);
#else
		printf(colorstrings[colorcode]);
#endif
		std::cout<<buf<<std::endl;
#ifdef WIN32
		SetConsoleTextAttribute(stderr_handle, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
#else
		printf(colorstrings[TNORMAL]);
#endif
		m_lock.unlock();
	}

	if(m_flags & LOG_STRING && m_file)
	{
		outTime(m_file);
		m_file<<buf<<std::endl;
	}
	
}

void Log::outNotice(const char* source, const char* str, ...)
{
	if(!source || !str)
		return;

	va_list ap;
	char buf[32768];
	va_start(ap, str);
	vsnprintf(buf, 32768, str, ap);
	va_end(ap);

	m_lock.lock();
#ifdef WIN32
	SetConsoleTextAttribute(stdout_handle, TWHITE);
#else
	printf(colorstrings[TWHITE]);
#endif
	std::cout<<"["<<source<<"] ";
#ifdef WIN32
	SetConsoleTextAttribute(stdout_handle, TNORMAL);
#else
	printf(colorstrings[TNORMAL]);
#endif
	std::cout<<buf<<std::endl;
	m_lock.unlock();
}

void Log::outTime(std::ofstream& file)
{
	time_t T = time(NULL);
	//char buffer[256];
	struct tm *tm = localtime(&T);
	std::string day = Desperion::ToString(tm->tm_mday);
	std::string month = Desperion::ToString(tm->tm_mon);
	std::string year = Desperion::ToString(tm->tm_year);
	std::string hour = Desperion::ToString(tm->tm_hour);
	std::string minute = Desperion::ToString(tm->tm_min);
	std::string second = Desperion::ToString(tm->tm_sec);
	while(day.size() < 2)
		day = "0" + day;
	while(month.size() < 2)
		month = "0" + month;
	while(hour.size() < 2)
		hour = "0" + hour;
	while(minute.size() < 2)
		minute = "0" + minute;
	while(second.size() < 2)
		second = "0" + second;
	std::string t = day + "/" + month + "/" + year + "~" + hour + ":" + minute + ":" + second + "\t";
	//strftime(buffer, 256, "[%Y-%m-%d %T] ", tm);
	file<<t;
}

void Log::outString( const char * str, ... )
{
	if(!str)
		return;

	va_list ap;
	char buf[32768];
	va_start(ap, str);
	vsnprintf(buf, 32768, str, ap);
	va_end(ap);

	if(m_flags & OUT_STRING)
	{
		m_lock.lock();
		std::cout<<buf<<std::endl;
		m_lock.unlock();
	}
	if(m_flags & LOG_STRING && m_file)
	{
		outTime(m_file);
		m_file<<buf<<std::endl;
	}
}

void Log::outError( const char * err, ... )
{
	if(!err)
		return;

	va_list ap;
	char buf[32768];
	va_start(ap, err);
	vsnprintf(buf, 32768, err, ap);
	va_end(ap);

	if(m_flags & OUT_ERROR)
	{
		m_lock.lock();
#ifdef WIN32
		SetConsoleTextAttribute(stderr_handle, FOREGROUND_RED | FOREGROUND_INTENSITY);
#else
		puts(colorstrings[TRED]);
#endif
		std::cerr<<buf<<std::endl;
#ifdef WIN32
		SetConsoleTextAttribute(stderr_handle, TNORMAL);
#else
		puts(colorstrings[TNORMAL]);
#endif
		m_lock.unlock();
	}
	if(m_flags & LOG_ERROR && m_errorFile)
	{
		outTime(m_errorFile);
		m_errorFile<<buf<<std::endl;
	}
}

void Log::outDebug( const char * str, ... )
{
	if(!str)
		return;

	va_list ap;
	char buf[32768];
	va_start(ap, str);
	vsnprintf(buf, 32768, str, ap);
	va_end(ap);

	if(m_flags & OUT_DEBUG)
	{
		m_lock.lock();
#ifdef WIN32
		SetConsoleTextAttribute(stderr_handle, TYELLOW);
#else
		puts(colorstrings[TYELLOW]);
#endif
		std::cout<<buf<<std::endl;
#ifdef WIN32
		SetConsoleTextAttribute(stderr_handle, TNORMAL);
#else
		puts(colorstrings[TNORMAL]);
#endif
		m_lock.unlock();
	}
	if(m_flags & LOG_DEBUG && m_debugFile)
	{
		outTime(m_debugFile);
		m_debugFile<<buf<<std::endl;
	}
}

Log::~Log()
{
	m_file.close();
	m_errorFile.close();
	m_debugFile.close();
}

void Log::Init(std::string path, uint32 flags)
{
	m_path = path;
	m_flags = flags;

	if (m_flags & LOG_STRING)
	{
		std::string filename = m_path + "/file.log";
		m_file.open(filename.c_str());
		if (m_file.fail())
			std::cerr<<__FUNCTION__<<": Error opening '"<<filename<<"': "<<strerror(errno)<<std::endl;
		m_file.clear();
	}

	if(m_flags & LOG_ERROR)
	{
		std::string filename = m_path + "/errors.log";
		m_errorFile.open(filename.c_str());
		if (m_errorFile.fail())
			std::cerr<<__FUNCTION__<<": Error opening '"<<filename<<"': "<<strerror(errno)<<std::endl;
		m_errorFile.clear();
	}

	if(m_flags & LOG_DEBUG)
	{
		std::string filename = m_path + "/debug.log";
		m_debugFile.open(filename.c_str());
		if (m_debugFile.fail())
			std::cerr<<__FUNCTION__<<": Error opening '"<<filename<<"': "<<strerror(errno)<<std::endl;
		m_debugFile.clear();
	}

	// get error handle
#ifdef WIN32
	stderr_handle = GetStdHandle(STD_ERROR_HANDLE);
	stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
}

