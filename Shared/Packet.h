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