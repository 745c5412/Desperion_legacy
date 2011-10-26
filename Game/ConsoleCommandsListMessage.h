#ifndef __CONSOLE_COMMANDS_LIST_MESSAGE__
#define __CONSOLE_COMMANDS_LIST_MESSAGE__

class ConsoleCommandsListMessage : public DofusMessage
{
public:
	virtual uint32 GetOpcode() const
	{ return SMSG_CONSOLE_COMMANDS_LIST; }

	ConsoleCommandsListMessage(std::vector<std::string>& aliases, std::vector<std::string>& arguments, std::vector<std::string>& descriptions)
	{
		uint16 size = aliases.size();
		m_buffer<<size;
		for(uint16 a = 0; a < size; ++a)
			m_buffer<<aliases[a];
		size = arguments.size();
		m_buffer<<size;
		for(uint16 a = 0; a < size; ++a)
			m_buffer<<arguments[a];
		size = descriptions.size();
		m_buffer<<size;
		for(uint16 a = 0; a < size; ++a)
			m_buffer<<descriptions[a];
	}
};

#endif