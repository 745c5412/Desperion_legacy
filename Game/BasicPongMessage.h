#ifndef __BASIC_PONG_MESSAGE__
#define __BASIC_PONG_MESSAGE__

class BasicPongMessage : public DofusMessage
{
public:
	virtual uint32 GetOpcode() const
	{ return SMSG_BASIC_PONG; }

	BasicPongMessage(bool quiet)
	{
		m_buffer<<quiet;
	}
};

#endif