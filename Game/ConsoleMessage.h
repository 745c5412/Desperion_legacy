#ifndef __CONSOLE_MESSAGE__
#define __CONSOLE_MESSAGE__

enum ConsoleMessageType
{
	CONSOLE_TEXT_MESSAGE = 0,
	CONSOLE_INFO_MESSAGE = 1,
	CONSOLE_ERR_MESSAGE = 2,
};

class ConsoleMessage : public DofusMessage
{
public:
	virtual uint32 GetOpcode() const
	{ return SMSG_CONSOLE; }

	ConsoleMessage(int8 type, std::string content)
	{
		m_buffer<<type<<content;
	}
};

#endif