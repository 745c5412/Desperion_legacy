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

#ifndef __QUERY_RESULT__
#define __QUERY_RESULT__

class Field
{
public:

	inline void SetValue(char* value) { m_value = value; }

	inline const char *GetString() { return m_value; }
	inline float GetFloat() { return m_value ? static_cast<float>(atof(m_value)) : 0; }
	inline bool GetBool() { return m_value ? atoi(m_value) > 0 : false; }
	inline uint8 GetUInt8() { return m_value ? static_cast<uint8>(atol(m_value)) : 0; }
	inline int8 GetInt8() { return m_value ? static_cast<int8>(atol(m_value)) : 0; }
	inline uint16 GetUInt16() { return m_value ? static_cast<uint16>(atol(m_value)) : 0; }
	inline int16 GetInt16() { return m_value ? static_cast<int16>(atol(m_value)) : 0; }
	inline uint32 GetUInt32() { return m_value ? static_cast<uint32>(atol(m_value)) : 0; }
	inline int32 GetInt32() { return m_value ? static_cast<int32>(atol(m_value)) : 0; }
	uint64 GetUInt64() 
	{
		if(m_value)
		{
			uint64 value;
#if !defined(WIN32) && defined(X64)
			sscanf(m_value,I64FMTD,(long long unsigned int*)&value);
#else
			sscanf(m_value,I64FMTD,&value);
#endif
			return value;
		}
		else
			return 0;
	}

	int64 GetInt64() 
	{
		if(m_value)
		{
			int64 value;
#if !defined(WIN32) && defined(X64)
			sscanf(m_value,I64FMTD,(long long int*)&value);
#else
			sscanf(m_value,SI64FMTD,&value);
#endif
			return value;
		}
		else
			return 0;
	}

private:
		char *m_value;
};

class QueryResult
{
public:
	QueryResult(MYSQL_RES *res, uint32 fields, uint32 rows);
	~QueryResult();

	bool NextRow();
	void Delete() { delete this; }

	inline Field* Fetch() { return m_currentRow; }
	inline uint32 GetFieldCount() const { return m_fieldCount; }
	inline uint32 GetRowCount() const { return m_rowCount; }

protected:
	uint32 m_fieldCount;
	uint32 m_rowCount;
    Field *m_currentRow;
	MYSQL_RES *m_result;
};

typedef boost::shared_ptr<QueryResult> ResultPtr;

#endif