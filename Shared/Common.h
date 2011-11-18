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
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#ifdef _MSC_VER

#define I64FMT "%016I64X"
#define I64FMTD "%I64u"
#define SI64FMTD "%I64d"
#define snprintf _snprintf
#define atoll __atoi64

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#include <CrashHandler.h>

inline bool CheckForDebugger()
{
    __try 
    {
        DebugBreak();
    }
    __except(GetExceptionCode() == EXCEPTION_BREAKPOINT ? 
             EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) 
    {
        // No debugger is attached, so return FALSE 
        // and continue.
        return false;
    }
    return true;
}

#else

#define stricmp strcasecmp
#define strnicmp strncasecmp
#define I64FMT "%016llX"
#define I64FMTD "%llu"
#define SI64FMTD "%lld"

#endif

#if COMPILER != COMPILER_GNU
typedef signed __int64 uint64;
typedef signed __int32 uint32;
typedef signed __int16 int16;
typedef signed __int8 int8;

typedef unsigned __int64 uint64;
typedef unsigned __int32 uint32;
typedef unsigned __int16 uint16;
typedef unsigned __int8 uint8;
#else
typedef uint64_t uint64;
typedef uint32_t uint32;
typedef int16_t int16;
typedef int8_t int8;
typedef int64_t int64;
typedef int32_t int32;
typedef uint16_t uint16;
typedef uint8_t uint8;
#endif

#define ASSERT( assertion ) { if( !(assertion) ) { fprintf( stderr, "\n%s:%i ASSERTION FAILED:\n  %s\n", __FILE__, __LINE__, #assertion ); assert(assertion); } }

#endif
