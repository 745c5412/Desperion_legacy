#ifndef __BASIC_TIME_MESSAGE__
#define __BASIC_TIME_MESSAGE__

class BasicTimeMessage : public DofusMessage
{
public:
	virtual uint32 GetOpcode() const
	{ return SMSG_BASIC_TIME; }

	BasicTimeMessage(int timestamp, int16 offset)
	{
		m_buffer<<timestamp<<offset;
	}
};

#endif