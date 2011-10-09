#ifndef __DATABASE__
#define __DATABASE__


/*
	Based on AscentEmulator Database class
*/

struct Connection
{
	MYSQL* conn;
	boost::mutex mymutex;
	Connection() {}
	Connection(const Connection& that){}
};

class Field
{
public:

	inline void SetValue(char* value) { mValue = value; }

	inline const char *GetString() { return mValue; }
	inline float GetFloat() { return mValue ? static_cast<float>(atof(mValue)) : 0; }
	inline bool GetBool() { return mValue ? atoi(mValue) > 0 : false; }
	inline uint8 GetUInt8() { return mValue ? static_cast<uint8>(atol(mValue)) : 0; }
	inline int8 GetInt8() { return mValue ? static_cast<int8>(atol(mValue)) : 0; }
	inline uint16 GetUInt16() { return mValue ? static_cast<uint16>(atol(mValue)) : 0; }
	inline int16 GetInt16() { return mValue ? static_cast<int16>(atol(mValue)) : 0; }
	inline uint32 GetUInt32() { return mValue ? static_cast<uint32>(atol(mValue)) : 0; }
	inline int32 GetInt32() { return mValue ? static_cast<int32>(atol(mValue)) : 0; }
	uint64 GetUInt64() 
	{
		if(mValue)
		{
			uint64 value;
#if !defined(WIN32) && defined(X64)
			sscanf(mValue,I64FMTD,(long long unsigned int*)&value);
#else
			sscanf(mValue,I64FMTD,&value);
#endif
			return value;
		}
		else
			return 0;
	}

	int64 GetInt64() 
	{
		if(mValue)
		{
			int64 value;
#if !defined(WIN32) && defined(X64)
			sscanf(mValue,I64FMTD,(long long int*)&value);
#else
			sscanf(mValue,SI64FMTD,&value);
#endif
			return value;
		}
		else
			return 0;
	}

private:
		char *mValue;
};

class QueryResult
{
public:
	QueryResult(MYSQL_RES *res, uint32 fields, uint32 rows);
	~QueryResult();

	bool NextRow();
	void Delete() { delete this; }

	inline Field* Fetch() { return mCurrentRow; }
	inline uint32 GetFieldCount() const { return mFieldCount; }
	inline uint32 GetRowCount() const { return mRowCount; }

protected:
	uint32 mFieldCount;
	uint32 mRowCount;
    Field *mCurrentRow;
	MYSQL_RES *mResult;
};

class Database
{
private:
	Connection * m_connections;

	std::string m_host_name;
	std::string m_user_name;
	std::string m_password;
	std::string m_database_name;
	uint16 m_port;
	uint8 m_connections_number;

	Connection* GetFreeConnection();
	bool SendQuery(Connection*, const char*, bool);
	QueryResult* StoreResult(Connection*);
	bool HandleError(Connection*, uint32);
	bool Reconnect(Connection*);
public:
	Database(uint8);
	~Database();

	bool Init(std::string, uint16, std::string, std::string, std::string);

	QueryResult* Query(const char*, ...);
	bool Execute(const char*, ...);
	void AsyncExecute(const char*, ...);
	bool _AsyncExecute(const char*);
};

#endif