#ifndef __ACQUAINTANCE_SEARCH_ERROR_MESSAGE__
#define __ACQUAINTANCE_SEARCH_ERROR_MESSAGE__

class AcquaintanceSearchErrorMessage : public DofusMessage
{
public:
	uint32 GetOpcode() const
	{ return SMSG_ACQUAINTANCE_SEARCH_ERROR; }

	AcquaintanceSearchErrorMessage(uint8 reason)
	{
		m_buffer<<reason;
	}
};

#endif