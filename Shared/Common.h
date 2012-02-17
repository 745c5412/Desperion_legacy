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

#ifndef __COMMON__
#define __COMMON__

#define _WIN32_WINNT NTDDI_WIN7 

#include <csignal>
#include <cstdio>
#include <boost/tr1/unordered_map.hpp>
#include <cstdlib>
#include <cstdarg>
#include <ctime>
#include <cmath>
#include <cerrno>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <string>
#include <exception>
#include <boost/asio.hpp>
#include <set>
#include <map>
#include <string>
#include <list>
#include <vector>
#include <boost/thread.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/threadpool.hpp>
#include <deque>
#include <cassert>
#include <fstream>
#include <iostream>
#include <mysql/mysql.h>
#include <libpq/libpq-fe.h>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <crypto/rng.h>
#include <crypto/hex.h>
#include <crypto/rsa.h>
#include <crypto/files.h>
#include <crypto/aes.h>
#include <crypto/modes.h>
#include <crypto/randpool.h>
#include <crypto/seed.h>
#include <crypto/osrng.h>
#include <crypto/md5.h>
#include <boost/bimap.hpp>
#include <tbb/concurrent_vector.h>
#include <tbb/atomic.h>
#include <tbb/parallel_while.h>
#include <tbb/concurrent_unordered_set.h>
#include <tbb/concurrent_queue.h>

// for Session => boost::bimap (friends / ennemies / ignored) [Game]
struct ci_char_traits : public std::char_traits<char>
{
	static bool eq(char c1, char c2)
	{
		return toupper(c1) == toupper(c2);
	}

	static bool ne(char c1, char c2)
	{
		return toupper(c1) != toupper(c2);
	}

	static bool lt(char c1, char c2)
	{
		return toupper(c1) < toupper(c2);
	}

	static int compare(const char* s1, const char* s2, size_t n)
	{
		return memicmp(s1, s2, n);
	}

	static const char* find(const char* s, int n, char a)
	{
		while((n-- > 0) && (toupper(*s) != toupper(a)))
			++s;
		return s;
	}
};

namespace std
{
	typedef std::basic_string<char, ci_char_traits> istring;
}

#ifdef _MSC_VER

#define I64FMT "%016I64X"
#define I64FMTD "%I64u"
#define SI64FMTD "%I64d"
#define atoll __atoi64

#include <CrashHandler.h>

inline bool CheckForDebugger()
{
	__try 
	{ DebugBreak(); }
	__except(GetExceptionCode() == EXCEPTION_BREAKPOINT ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) 
	{ return false; }
	return true;
}

#else

#define I64FMT "%016llX"
#define I64FMTD "%llu"
#define SI64FMTD "%lld"

#endif

typedef unsigned long long int uint64;
typedef unsigned int uint32;
typedef signed short int16;
typedef signed char int8;
typedef signed long long int int64;
typedef signed int int32;
typedef unsigned short uint16;
typedef unsigned char uint8;

#endif
