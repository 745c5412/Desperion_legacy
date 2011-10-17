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

#ifndef __BYTE_BUFFER__
#define __BYTE_BUFFER__

inline void SwapBytes(uint8 *p, size_t n)
{
    size_t lo, hi;
    for(lo=0, hi=n-1; hi>lo; lo++, hi--)
    {
        char tmp=p[lo];
        p[lo] = p[hi];
        p[hi] = tmp;
    }
}

enum Endianness
{
	LITTLE_ENDIAN,
	BIG_ENDIAN,
};

inline Endianness GetEndianness()
{

	union {
		int i;
		char c[sizeof(int)];
	} x;
	x.i = 1;
	if(x.c[0] == 1)
		return LITTLE_ENDIAN;
	else
		return BIG_ENDIAN;
}


#define DEFAULT_SIZE 0x1000

class ByteBuffer
{
private:
	size_t m_rpos;
	size_t m_wpos;
	std::vector<uint8> m_data;
public:
	static Endianness ENDIANNESS;

	ByteBuffer() : m_rpos(0), m_wpos(0)
	{ m_data.reserve(DEFAULT_SIZE); }

	ByteBuffer(const ByteBuffer& that) : m_rpos(that.m_rpos), m_wpos(that.m_wpos), m_data(that.m_data)
	{ }

	size_t GetReadPos() const
	{ return m_rpos; }

	size_t GetWritePos() const
	{ return m_wpos; }

	void SetReadPos(size_t pos)
	{ m_rpos = pos; }

	void HexLike()
	{
		uint32 j = 1, k = 1;
		size_t s = Size();
		printf("STORAGE_SIZE: %u\n", (unsigned int)s );
		for(uint32 i = 0; i < s; ++i)
		{
			if (Read<uint8>(i) < 0x0F)
			{
				printf("0%X ", Read<uint8>(i) );
			}
			else
			{
				printf("%X ", Read<uint8>(i) );
			}
		}
		printf("\n");
	}

	void Clear()
	{
		m_data.clear();
		m_rpos = m_wpos = 0;
	}

	uint8 operator[](size_t pos) {
		return Read<uint8>(pos);
	}

	inline size_t Size() const
	{ return m_data.size(); }

	template<class T>
	void Append(T value)
	{
		size_t size = sizeof(value);
		uint8* raw = (uint8*)&value;
		if(ByteBuffer::ENDIANNESS == LITTLE_ENDIAN)
			SwapBytes(raw, size);
		AppendBytes(raw, size);
	}

	template<class T>
	T Read()
	{ 
		T value = Read<T>(m_rpos); 
		if(ByteBuffer::ENDIANNESS == LITTLE_ENDIAN)
			SwapBytes((uint8*)&value, sizeof(T));
		m_rpos += sizeof(T);
		return value;
	}

	const uint8* Contents() const
	{ return &m_data[0]; }

	template<class T>
	T Read(size_t pos)
	{
		T value = 0;
		size_t size = sizeof(T);
		if(pos + size <= Size())
			value = *((T*)&m_data[pos]);
		return value;
	}

	void AppendBytes(const uint8* bytes, size_t count)
	{
		if(count == 0)
			return;
		if (m_data.size() < m_wpos + count)
			m_data.resize(m_wpos + count);
		memcpy(&m_data[m_wpos], bytes, count);
		m_wpos += count;
	}

	ByteBuffer& operator<<(uint8 value)
	{
		Append<uint8>(value);
		return *this;
	}

	ByteBuffer& operator<<(uint16 value)
	{
		Append<uint16>(value);
		return *this;
	}

	ByteBuffer& operator<<(uint32 value)
	{
		Append<uint32>(value);
		return *this;
	}

	ByteBuffer& operator<<(uint64 value)
	{
		Append<uint64>(value);
		return *this;
	}

	ByteBuffer& operator<<(int8 value)
	{
		Append<int8>(value);
		return *this;
	}

	ByteBuffer& operator<<(int16 value)
	{
		Append<int16>(value);
		return *this;
	}

	ByteBuffer& operator<<(int32 value)
	{
		Append<int32>(value);
		return *this;
	}

	ByteBuffer& operator<<(int64 value)
	{
		Append<int64>(value);
		return *this;
	}

	ByteBuffer& operator<<(double value)
	{
		Append<double>(value);
		return *this;
	}

	ByteBuffer& operator<<(float value)
	{
		Append<float>(value);
		return *this;
	}

	ByteBuffer& operator<<(bool value)
	{
		Append<uint8>(value ? 1 : 0);
		return *this;
	}

	ByteBuffer& operator<<(std::string value)
	{
		size_t s = value.length();
		size_t temp = s;
		Append<uint16>(temp);
		AppendBytes((uint8*)value.c_str(), s);
		return *this;
	}

	ByteBuffer& operator<<(const ByteBuffer& value)
	{
		size_t size = value.Size();
		if(size != 0)
			AppendBytes(value.Contents(), size);
		return *this;
	}

	template<class T>
	ByteBuffer& operator>>(T& value)
	{
		value = Read<T>();
		return *this;
	}
};

template<> inline ByteBuffer& ByteBuffer::operator>>(std::string& value)
{
	uint16 size = Read<uint16>();
	for(uint16 a = 0; a < size; ++a)
		value += Read<char>();
	return *this;
}

#endif
