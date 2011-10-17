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
	OUT_DEBUG = 1,
	LOG_DEBUG = 2,
	OUT_ERROR = 4,
	LOG_ERROR = 8,
	OUT_STRING = 16,
	LOG_STRING = 32,
};

#define OUTLOG_ALL OUT_DEBUG | LOG_DEBUG | OUT_ERROR | LOG_ERROR | OUT_STRING | LOG_STRING

class Log : public Singleton<Log>
{
public:
	~Log();

	void outString(const char *, ...);
	void outError(const char *, ...);
	void outNotice(const char *, const char *, ...);
	void outDebug(const char *, ...);
	void outTime(std::ofstream&);
	void outColor(uint32, const char *, ...);
	void Init(std::string, uint32 flags = 0);
private:
#ifdef _WIN32
	HANDLE stderr_handle;
	HANDLE stdout_handle;
#endif
	uint8 m_fileLogLevel;
	uint8 m_screenLogLevel;
	uint32 m_flags;

	std::string m_path;
	std::ofstream m_file;
	std::ofstream m_errorFile;
	std::ofstream m_debugFile;
	boost::mutex m_lock;
};

class AtomicLog
{
public:
	AtomicLog(std::string, uint32);
	void String(std::ostringstream&, bool line = true);
	void Error(std::ostringstream&, bool line = true);
	void Debug(std::ostringstream&, bool line = true);
	void Line();
private:
	void PutName();

	std::string m_name;
	uint32 m_color;
};

#endif
