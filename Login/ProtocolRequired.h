#ifndef __PROTOCOL_REQUIRED__
#define __PROTOCOL_REQUIRED__

class ProtocolRequired : public DofusMessage
{
public:
	uint32 GetOpcode() const
	{ return SMSG_PROTOCOL_REQUIRED; }

	ProtocolRequired(int requiredVersion, int currentVersion)
	{
		m_buffer<<requiredVersion<<currentVersion;
	}

};

#endif