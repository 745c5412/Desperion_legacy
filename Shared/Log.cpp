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
#include <boost/filesystem.hpp>

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

void Log::OutColor(uint32 colorcode, const char * str, ...) // s'affiche obligatoirement à l'écran
{
	if(!str) 
		return;
	va_list ap;
	char buf[32768];
	va_start(ap, str);
	vsnprintf(buf, 32768, str, ap);
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
}

void Log::OutNotice(const std::string& source, const char* str, ...) // idem
{
	if(!str)
		return;
	va_list ap;
	char buf[32768];
	va_start(ap, str);
	vsnprintf(buf, 32768, str, ap);
	va_end(ap);

	PrintTime();
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
}

void Log::OutTime(std::ofstream& file)
{
	file<<Desperion::FormatTime("[%H:%M:%S] ");
}

void Log::PrintTime()
{
	std::cout<<Desperion::FormatTime("[%H:%M] ");
}

void Log::_OutString(boost::shared_array<const char> str)
{
	OutTime(m_file);
	m_file<<"[INFO] "<<str.get()<<std::endl;
}

void Log::OutString(const char * str, ...)
{
	if(!str)
		return;
	if(!GET(m_flags, PRINT_STRING) && !GET(m_flags, OUT_STRING))
		return;
	va_list ap;
	char buf[32768];
	va_start(ap, str);
	vsnprintf(buf, 32768, str, ap);
	va_end(ap);

	if(GET(m_flags, PRINT_STRING))
	{
		PrintTime();
		std::cout<<buf<<std::endl;
	}
	if(GET(m_flags, OUT_STRING))
	{
		size_t size = strlen(buf);
		char* dynBuf = new char[size + 1];
		memcpy(dynBuf, buf, size + 1);
		m_service.post(boost::bind(&Log::_OutString, this, boost::shared_array<const char>(dynBuf)));
	}
}

void Log::_OutError(boost::shared_array<const char> str)
{
	OutTime(m_file);
	m_file<<"[ERROR] "<<str.get()<<std::endl;
}

void Log::OutError(const char * err, ...)
{
	if(!err)
		return;
	if(!GET(m_flags, PRINT_ERROR) && !GET(m_flags, OUT_ERROR))
		return;
	va_list ap;
	char buf[32768];
	va_start(ap, err);
	vsnprintf(buf, 32768, err, ap);
	va_end(ap);

	if(GET(m_flags, PRINT_ERROR))
	{
		PrintTime();
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
	if(GET(m_flags, OUT_ERROR))
	{
		size_t size = strlen(buf);
		char* dynBuf = new char[size + 1];
		memcpy(dynBuf, buf, size + 1);
		m_service.post(boost::bind(&Log::_OutError, this, boost::shared_array<const char>(dynBuf)));
	}
}

void Log::_OutDebug(boost::shared_array<const char> str)
{
	
	OutTime(m_file);
	m_file<<"[DEBUG] "<<str.get()<<std::endl;
}

void Log::OutDebug(const char * str, ...)
{
	if(!str)
		return;
	if(!GET(m_flags, PRINT_DEBUG) && !GET(m_flags, OUT_DEBUG))
		return;
	va_list ap;
	char buf[32768];
	va_start(ap, str);
	vsnprintf(buf, 32768, str, ap);
	va_end(ap);

	if(GET(m_flags, PRINT_DEBUG))
	{
		PrintTime();
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
	if(GET(m_flags, OUT_DEBUG))
	{
		size_t size = strlen(buf);
		char* dynBuf = new char[size + 1];
		memcpy(dynBuf, buf, size + 1);
		m_service.post(boost::bind(&Log::_OutError, this, boost::shared_array<const char>(dynBuf)));
	}
}

void Log::OutSession(std::ofstream& file, boost::shared_array<const char> str)
{
	OutTime(file);
	file<<str.get()<<std::endl;
}

void CreateDirectoryIfNotExists(const char* path)
{
	boost::filesystem::path p(path);
	if(!boost::filesystem::exists(p) || !boost::filesystem::is_directory(p))
	{
		boost::system::error_code ec;
		boost::filesystem::create_directory(p, ec);
		if(ec)
			std::cerr<<"Error creating 'logs' directory: ["<<ec.value()<<"] "<<ec.message();
	}
}

void Log::Init(const char* path, uint8 flags)
{
	CreateDirectoryIfNotExists(path);
	CreateDirectoryIfNotExists("sessions");
	m_flags = flags;
	std::string time = Desperion::FormatTime("%d-%m-%y");
	if (GET(m_flags, OUT_STRING) || GET(m_flags, OUT_ERROR) || GET(m_flags, OUT_DEBUG))
	{
		std::string strPath = std::string(path);
		char end = strPath.size() > 0 ? strPath.at(strPath.size() - 1) : 0;
		std::string filename = strPath + (end == '\\' || end == '/' ? "" : "/") + "file_" + time + ".log";
		m_file.open(filename.c_str(), std::ios::app);
		if (m_file.fail())
			std::cerr<<__FUNCTION__<<": Error opening '"<<filename<<"'"<<std::endl;
	}
#ifdef WIN32
	stderr_handle = GetStdHandle(STD_ERROR_HANDLE);
	stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
}

