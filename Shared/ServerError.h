#ifndef __SERVER_ERROR__
#define __SERVER_ERROR__

class ServerError : public std::exception
{
public:
	ServerError(const char* const str) : std::exception(str)
	{
	}
};

#endif