#ifndef __HELLO_CONNECT_MESSAGE__
#define __HELLO_CONNECT_MESSAGE__

class HelloConnectMessage : public DofusMessage
{
public:
	uint32 GetOpcode() const
	{ return SMSG_HELLO_CONNECT; }

	HelloConnectMessage(int8 connectionType, std::string key)
	{
		m_buffer<<connectionType<<key;
	}
};

#endif