#ifndef __DOFUS_MESSAGE__
#define __DOFUS_MESSAGE__

class DofusMessage
{
protected:
	ByteBuffer m_buffer;
public:
	virtual uint32 GetOpcode() const = 0;

	const ByteBuffer& GetBuffer() const
	{ return m_buffer; }

	DofusMessage()
	{
	}
};

#endif