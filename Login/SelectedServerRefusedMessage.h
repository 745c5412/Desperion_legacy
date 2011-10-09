#ifndef __SELECTED_SERVER_REFUSED_MESSAGE__
#define __SELECTED_SERVER_REFUSED_MESSAGE__

class SelectedServerRefusedMessage : public DofusMessage
{
public:
	uint32 GetOpcode() const
	{ return SMSG_SELECTED_SERVER_REFUSED; }

	SelectedServerRefusedMessage(int16 id, int8 reason, int8 state)
	{
		m_buffer<<id<<reason<<state;
	}
};

#endif