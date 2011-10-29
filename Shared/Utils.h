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

#ifndef __UTILS__
#define __UTILS__

namespace Desperion
{

	template<class U>
	inline bool FromString(const std::string& string, U& dest, bool conv = false) {
		std::istringstream iss(string);
		if(conv)
			return iss >> std::hex >> dest != 0;
		else
			return iss >> dest != 0;
	}

	template<>
	inline bool FromString<uint8>(const std::string& string, uint8& dest, bool conv) {
		std::istringstream iss(string);
		uint16 dest2;
		if(conv)
		{
			bool b = iss >> std::hex >> dest2 != 0;
			dest = dest2;
			return b;
		}
		else
		{
			bool b = iss >> dest2 != 0;
			dest = dest2;
			return b;
		}
	}

	template<>
	inline bool FromString<int8>(const std::string& string, int8& dest, bool conv) {
		std::istringstream iss(string);
		int16 dest2;
		if(conv)
		{
			bool b = iss >> std::hex >> dest2 != 0;
			dest = dest2;
			return b;
		}
		else
		{
			bool b = iss >> dest2 != 0;
			dest = dest2;
			return b;
		}
	}

	template<class W>
	inline std::string ToHexString(const W& i){
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
	inline std::string ToString(const V& i) {
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

	std::string ToLowerCase(std::string str);
	void Split(std::vector<std::string>& vector, std::string str, char sep);

	template<char S>
	inline void FastSplit(std::vector<std::string>& vector, std::string& str, bool reserved = false)
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

	inline int SplitInt(std::string& str)
	{ 
		return atoi(str.c_str());
	}

	template<char S, class T, class V>
	inline void FastSplit(std::vector<T>& vector, std::string& str, V callback, bool reserved = false)
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

	std::string ToUpperCase(std::string str);
	void SetApplicationTitle(std::string title); 
	int IndexOf(std::string str, char tofind);

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

	inline ByteBuffer DbToBuffer(std::string db)
	{
		ByteBuffer buffer;
		std::string temp = "";
		for(int a = 0; a < db.size(); ++a)
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
}
#endif