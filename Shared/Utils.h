#ifndef __UTILS__
#define __UTILS__

namespace Desperion
{

	template<class U>
	inline bool FromString(const std::string& string, U& dest, bool conv = false);

	template<class U>
	bool FromString(const std::string& string, U& dest, bool conv) {
		std::istringstream iss(string);
		if(conv)
			return iss >> std::hex >> dest != 0;
		else
			return iss >> dest != 0;
	}

	template<>
	inline bool FromString<uint8>(const std::string& string, uint8& dest, bool conv);

	template<>
	bool FromString<uint8>(const std::string& string, uint8& dest, bool conv) {
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
	inline bool FromString<int8>(const std::string& string, int8& dest, bool conv);

	template<>
	bool FromString<int8>(const std::string& string, int8& dest, bool conv) {
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
	inline std::string ToHexString(const W& object);

	template<class W>
	std::string ToHexString(const W& i){
		std::stringstream ss;
		ss<<std::hex<<std::showbase<<i;
		return ss.str();
	}

	template<>
	inline std::string ToHexString<uint8>(const uint8& object);

	template<>
	std::string ToHexString<uint8>(const uint8& i)
	{
		uint16 ii = i;
		std::stringstream ss;
		ss<<std::hex<<std::showbase<<ii;
		return ss.str();
	}

	template<>
	inline std::string ToHexString<int8>(const int8& object);

	template<>
	std::string ToHexString<int8>(const int8& i)
	{
		int16 ii = i;
		std::stringstream ss;
		ss<<std::hex<<std::showbase<<ii;
		return ss.str();
	}

	template<class V>
	inline std::string ToString(const V& object);

	template<class V>
	std::string ToString(const V& i) {
		std::ostringstream oss;
		oss<<i;
		return oss.str();
	}

	template<>
	inline std::string ToString<uint8>(const uint8& object);

	template<> 
	std::string ToString<uint8>(const uint8& i)
	{
		std::ostringstream oss;
		uint16 ii = i;
		oss<<ii;
		return oss.str();
	}

	template<>
	inline std::string ToString<int8>(const int8& object);

	template<> 
	std::string ToString<int8>(const int8& i)
	{
		std::ostringstream oss;
		int16 ii = i;
		oss<<ii;
		return oss.str();
	}

	std::string ToLowerCase(std::string str);
	void Split(std::vector<std::string>& vector, std::string str, char sep);
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