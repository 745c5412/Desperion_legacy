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

#ifndef __PACKET__
#define __PACKET__

class Packet
{
public:
	static uint8 ComputeTypeLen(size_t size)
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

	static void Pack(uint16 opcode, ByteBuffer& dest, ByteBuffer& src)
	{
		size_t size = src.Size();
		uint8 compute = ComputeTypeLen(size);
		uint16 value = (opcode << 2) | compute;
		dest<<value;
		switch(compute)
		{
		case 1:
			dest<<uint8(size);
			break;
		case 2:
			dest<<uint16(size);
			break;
		case 3:
			uint8 num2 = (size >> 0x10) & 0xff;
            uint16 num3 = size & 0xffff;
			dest<<num2<<num3;
			break;
		}
		if(size > 0)
			dest.AppendBytes(src.Contents(), size);
	}
};

#endif