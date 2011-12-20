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

void Log::outColor(uint32 colorcode, const char * str, ...) // s'affiche obligatoirement à l'écran
{
	if(!str) 
		return;

	boost::mutex::scoped_lock lock(m_lock);
	va_list ap;
	char buf[32768];
	va_start(ap, str);
	vsnprintf_s(buf, 32768, str, ap);
	va_end(ap);

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

	if(m_file)
		m_file<<buf<<std::endl;
}

void Log::outNotice(const char* source, const char* str, ...) // idem
{
	if(!source || !str)
		return;

	boost::mutex::scoped_lock lock(m_lock);
	va_list ap;
	char buf[32768];
	va_start(ap, str);
	vsnprintf_s(buf, 32768, str, ap);
	va_end(ap);

	printTime();
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

	if(m_file)
	{
		outTime(m_file);
		m_file<<"["<<source<<"] "<<buf<<std::endl;
	}
}

void Log::outTime(std::ofstream& file)
{
	file<<Desperion::FormatTime("[%H:%M:%S] ");
}

void Log::printTime()
{
	std::cout<<Desperion::FormatTime("[%H:%M] ");
}

void Log::outString( const char * str, ... )
{
	if(!str)
		return;
	bool print = GET(m_flags, PRINT_STRING), out = GET(m_flags, OUT_STRING);
	if(!print && !out)
		return;

	boost::mutex::scoped_lock lock(m_lock);
	va_list ap;
	char buf[32768];
	va_start(ap, str);
	vsnprintf_s(buf, 32768, str, ap);
	va_end(ap);

	if(print)
	{
		printTime();
		std::cout<<buf<<std::endl;
	}
	if(m_file && out)
	{
		outTime(m_file);
		m_file<<buf<<std::endl;
	}
}

void Log::outFile(std::ofstream& file, std::string str)
{
	if(!file)
		return;
	outTime(file);
	file<<str<<std::endl;
}

void Log::outError(const char * err, ... )
{
	if(!err)
		return;
	bool print = GET(m_flags, PRINT_ERROR), out = GET(m_flags, OUT_ERROR);
	if(!print && !out)
		return;

	boost::mutex::scoped_lock lock(m_lock);
	va_list ap;
	char buf[32768];
	va_start(ap, err);
	vsnprintf_s(buf, 32768, err, ap);
	va_end(ap);

	if(print)
	{
		printTime();
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
	}
	if(m_errorFile && out)
	{
		outTime(m_errorFile);
		m_errorFile<<buf<<std::endl;
	}
}

void Log::outDebug( const char * str, ... )
{
	if(!str)
		return;
	bool print = GET(m_flags, PRINT_DEBUG), out = GET(m_flags, OUT_DEBUG);
	if(!print && !out)
		return;

	boost::mutex::scoped_lock lock(m_lock);
	va_list ap;
	char buf[32768];
	va_start(ap, str);
	vsnprintf_s(buf, 32768, str, ap);
	va_end(ap);

	if(print)
	{
		printTime();
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
	}
	if(m_debugFile && out)
	{
		outTime(m_debugFile);
		m_debugFile<<buf<<std::endl;
	}
}

Log::~Log()
{
}

void Log::Init(std::string path, uint8 flags)
{
	m_path = path;
	m_flags = flags;

	std::string time = Desperion::FormatTime("%d-%m-%y_%H-%M-%S");
	if (GET(m_flags, OUT_STRING))
	{
		
		std::string filename = m_path + "/file_" + time + ".log";
		m_file.open(filename.c_str());
		if (m_file.fail())
			std::cerr<<__FUNCTION__<<": Error opening '"<<filename<<"'"<<std::endl;
		m_file.clear();
	}

	if(GET(m_flags, OUT_ERROR))
	{
		std::string filename = m_path + "/errors_" + time + ".log";
		m_errorFile.open(filename.c_str());
		if (m_errorFile.fail())
			std::cerr<<__FUNCTION__<<": Error opening '"<<filename<<"'"<<std::endl;
		m_errorFile.clear();
	}

	if(GET(m_flags, OUT_DEBUG))
	{
		std::string filename = m_path + "/debug_" + time + ".log";
		m_debugFile.open(filename.c_str());
		if (m_debugFile.fail())
			std::cerr<<__FUNCTION__<<": Error opening '"<<filename<<"'"<<std::endl;
		m_debugFile.clear();
	}

	// get error handle
#ifdef WIN32
	stderr_handle = GetStdHandle(STD_ERROR_HANDLE);
	stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
}

