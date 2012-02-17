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

#ifndef __LOG__
#define __LOG__

#ifdef WIN32

#define TRED FOREGROUND_RED | FOREGROUND_INTENSITY
#define TGREEN FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define TYELLOW FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY
#define TNORMAL FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE
#define TWHITE TNORMAL | FOREGROUND_INTENSITY
#define TBLUE FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define TPURPLE FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY

#else

#define TRED 1
#define TGREEN 2
#define TYELLOW 3
#define TNORMAL 4
#define TWHITE 5
#define TBLUE 6
#define TPURPLE 7

#endif

enum LogLevel
{
	PRINT_DEBUG = 0,
	OUT_DEBUG = 3,
	PRINT_ERROR = 1,
	OUT_ERROR = 4,
	PRINT_STRING = 2,
	OUT_STRING = 5,
};

#define SET(flag, bit) (((flag) |= (1 << (bit))) != 0)
#define CLEAR(flag, bit) (((flag) &= ~(1 << (bit))) != 0)
#define GET(flag, bit) (((flag) & (1 << (bit))) != 0)

class Log : public Singleton<Log>
{
public:
	Log(boost::asio::io_service& ios) : m_service(ios)
	{
	}

	void OutString(const char *, ...);
	void OutError(const char *, ...);
	void OutNotice(const std::string&, const char *, ...);
	void OutDebug(const char *, ...);
	void OutColor(uint32, const char *, ...);
	void OutSession(std::ofstream&, boost::shared_array<const char>);
	void Init(const char*, uint8 flags = 0xff);

private:
	void OutTime(std::ofstream&);
	void PrintTime();
	void _OutString(boost::shared_array<const char>);
	void _OutError(boost::shared_array<const char>);
	void _OutDebug(boost::shared_array<const char>);

#ifdef _WIN32
	HANDLE stderr_handle;
	HANDLE stdout_handle;
#endif

	uint8 m_flags;
	std::ofstream m_file;
	boost::asio::io_service& m_service;
};

#endif
