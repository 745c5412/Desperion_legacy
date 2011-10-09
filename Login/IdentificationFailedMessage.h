#ifndef __IDENTIFICATION_FAILED_MESSAGE__
#define __IDENTIFICATION_FAILED_MESSAGE__

class IdentificationFailedMessage : public DofusMessage
{
public:
	uint32 GetOpcode() const
	{ return SMSG_IDENTIFICATION_FAILED; }

	IdentificationFailedMessage(uint8 reason)
	{
		m_buffer<<reason;
	}
};

#endif