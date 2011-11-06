#ifndef __BASIC_DATE_MESSAGE__
#define __BASIC_DATE_MESSAGE__

class BasicDateMessage : public DofusMessage
{
public:
	virtual uint32 GetOpcode() const
	{ return SMSG_BASIC_DATE; }

	BasicDateMessage(int8 day, int8 month, int16 year)
	{
		m_buffer<<day<<month<<year;
	}
};

#endif