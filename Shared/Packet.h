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

#ifndef __PACKET__
#define __PACKET__

class Packet : public ByteBuffer
{
private:
	uint32 m_opcode;
public:
	uint16 ComputeTypeLen(size_t size) const
	{
		if(size > 0xffff)
			return 3;
		else if(size > 0xff)
			return 2;
		else if(size > 0)
			return 1;
		else
			return 0;
	}

	Packet(uint32 opcode)
	{
		m_opcode = opcode;
	}

	ByteBuffer Pack() const
	{
		size_t size = Size();
		uint16 compute = ComputeTypeLen(size);
		ByteBuffer buffer;
		uint16 value = (m_opcode << 2) | compute;
		buffer<<value;
		switch(compute)
		{
		case 1:
			buffer<<uint8(size);
			break;
		case 2:
			buffer<<uint16(size);
			break;
		case 3:
			uint8 num2 = (size >> 0x10) & 0xff;
            uint16 num3 = size & 0xffff;
			buffer<<uint8(num2);
			buffer<<uint16(num3);
			break;
		}
		if(size > 0)
			buffer.AppendBytes(Contents(), size);
		return buffer;
	}
};

#endif