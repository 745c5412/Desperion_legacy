#ifndef __COMMON__
#define __COMMON__

#include <signal.h>
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
#include <assert.h>
#include <fstream>
#include <iostream>
#include <mysql/mysql.h>

#if COMPILER == COMPILER_MICROSOFT

#define I64FMT "%016I64X"
#define I64FMTD "%I64u"
#define SI64FMTD "%I64d"
#define snprintf _snprintf
#define atoll __atoi64

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

#ifdef _WIN32
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#endif
