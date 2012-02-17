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

#ifndef __UTILS__
#define __UTILS__

namespace Desperion
{
	template<class U>
	inline bool FromString(const std::string& string, U& dest, bool conv = false)
	{
		std::istringstream iss(string);
		return conv ? (iss>>std::hex>>dest != 0) : (iss>>dest != 0);
	}

	template<>
	inline bool FromString<uint8>(const std::string& string, uint8& dest, bool conv)
	{
		std::istringstream iss(string);
		uint16 dest2;
		bool b = conv ? (iss>>std::hex>>dest2 != 0) : (iss>>dest2 != 0);
		dest = static_cast<uint8>(dest2);
		return b;
	}

	template<>
	inline bool FromString<int8>(const std::string& string, int8& dest, bool conv)
	{
		std::istringstream iss(string);
		int16 dest2;
		bool b = conv ? (iss>>std::hex>>dest2 != 0) : (iss>>dest2 != 0);
		dest = static_cast<int8>(dest2);
		return b;
	}

	template<class W>
	inline std::string ToHexString(const W& i)
	{
		std::stringstream ss;
		ss<<std::hex<<std::showbase<<i;
		return ss.str();
	}

	template<>
	inline std::string ToHexString<uint8>(const uint8& i)
	{
		uint16 ii = i;
		std::stringstream ss;
		ss<<std::hex<<std::showbase<<ii;
		return ss.str();
	}

	template<>
	inline std::string ToHexString<int8>(const int8& i)
	{
		int16 ii = i;
		std::stringstream ss;
		ss<<std::hex<<std::showbase<<ii;
		return ss.str();
	}

	template<class V>
	inline std::string ToString(const V& i)
	{
		std::ostringstream oss;
		oss<<i;
		return oss.str();
	}

	template<> 
	inline std::string ToString<uint8>(const uint8& i)
	{
		std::ostringstream oss;
		uint16 ii = i;
		oss<<ii;
		return oss.str();
	}

	template<> 
	inline std::string ToString<int8>(const int8& i)
	{
		std::ostringstream oss;
		int16 ii = i;
		oss<<ii;
		return oss.str();
	}

	template<char S>
	inline void FastSplitString(std::vector<std::string>& vector, const std::string& str, bool reserved = false)
	{
		std::string temp = "";
		for(uint16 a = 0; a < str.size(); ++a)
		{
			char b = str[a];
			switch(b)
			{
			case S:
				if(!reserved)
					vector.reserve(atoi(temp.c_str()));
				else
					vector.push_back(temp);
				reserved = true;
				temp.clear();
				break;
			default:
				temp += b;
			}
		}
		if(reserved && !temp.empty())
			vector.push_back(temp);
	}

	inline double SplitDouble(std::string& str)
	{
		return atof(str.c_str());
	}

	inline int SplitInt(std::string& str)
	{ 
		return atoi(str.c_str());
	}

	template<char S, class T, class V>
	inline void FastSplit(std::vector<T>& vector, const std::string& str, V callback, bool reserved = false)
	{
		std::string temp = "";
		for(uint16 a = 0; a < str.size(); ++a)
		{
			char b = str[a];
			switch(b)
			{
			case S:
				if(!reserved)
					vector.reserve(atoi(temp.c_str()));
				else
					vector.push_back(callback(temp));
				reserved = true;
				temp.clear();
				break;
			default:
				temp += b;
			}
		}
		if(reserved && !temp.empty())
			vector.push_back(callback(temp));
	}

	template<char S, class T, class V>
	inline void FastSplitSet(std::set<T>& set, const std::string& str, V callback)
	{
		std::string temp = "";
		for(uint16 a = 0; a < str.size(); ++a)
		{
			char b = str[a];
			switch(b)
			{
			case S:
				set.insert(callback(temp));
				temp.clear();
				break;
			default:
				temp += b;
			}
		}
		if(!temp.empty())
			set.insert(callback(temp));
	}

	template<char S>
	inline void FastSplitStringSet(std::set<std::string>& set, const std::string& str)
	{
		std::string temp = "";
		for(uint16 a = 0; a < str.size(); ++a)
		{
			char b = str[a];
			switch(b)
			{
			case S:
				set.insert(temp);
				temp.clear();
				break;
			default:
				temp += b;
			}
		}
		if(!temp.empty())
			set.insert(temp);
	}

	inline int IndexOf(const std::string& c1, char c2)
	{
		for(uint32 a = 0; a < c1.size(); a++)
		{
			if(c1[a] == c2)
				return a;
		}
		return -1;
	}

	inline std::string ToUpperCase(const std::string& str)
	{
		std::string buffer = "";
		for(uint32 i = 0; i < str.size(); ++i)
			buffer += std::toupper(str[i]);
		return buffer;
	}

	inline std::string ToLowerCase(const std::string& str)
	{	
		std::string buffer = "";
		for(uint32 i = 0; i < str.size(); ++i)
			buffer += std::tolower(str[i]);
		return buffer;
	}

	inline std::string BufferToDb(const ByteBuffer& buffer)
	{
		std::ostringstream db;
		size_t size = buffer.Size();
		if(size == 0)
			return "";
		const uint8* contents = buffer.Contents();
		for(uint32 a = 0; a < size; ++a)
		{
			if(a != 0)
				db<<" ";
			db<<uint16(contents[a]);
		}
		return db.str();
	}

	inline ByteBuffer DbToBuffer(std::string& db)
	{
		ByteBuffer buffer;
		std::string temp = "";
		for(size_t a = 0; a < db.size(); ++a)
		{
			char c = db[a];
			if(c == ' ')
			{
				int byte = atoi(temp.c_str());
				buffer<<uint8(byte);
				temp.clear();
			}
			else
				temp += c;
		}
		return buffer;
	}

	inline std::istring ComputeMD5Digest(std::string& src)
	{
		CryptoPP::MD5 hash;
		uint8 digest[CryptoPP::MD5::DIGESTSIZE];
		hash.CalculateDigest(digest, (const byte*)src.c_str(), src.length());
		CryptoPP::HexEncoder encoder;
		std::string output;
		encoder.Attach(new CryptoPP::StringSink(output));
		encoder.Put(digest, sizeof(digest));
		encoder.MessageEnd();
		return std::istring(output.c_str());
	}

	inline std::string FormatTime(const char* format)
	{
		time_t rawtime;
		struct tm * time_info = NULL;
		char buf[80];
		time(&rawtime);
		time_info = localtime(&rawtime);
		strftime(buf, 80, format, time_info);
		return std::string(buf);
	}

	inline boost::shared_array<const char> FormatString(const char* format, ...)
	{
		char sql[32768];
		va_list vlist;
		va_start(vlist, format);
		vsnprintf(sql, 32768, format, vlist);
		va_end(vlist);
		size_t size = strlen(sql);
		char* buf = new char[size + 1];
		memcpy(buf, sql, size + 1);
		return boost::shared_array<const char>(buf);
	}

	inline void SetApplicationTitle(const char* title, ...)
	{
		char buf[80];
		va_list ap;
		va_start(ap, title);
		vsnprintf(buf, 80, title, ap);
		va_end(ap);

#ifdef _WIN32
		std::string command = "TITLE " + std::string(buf);
		system(command.c_str());
#else
		std::cout<<"\033]0;"<<titre.c_str()<<"\007";
#endif
	}
}
#endif