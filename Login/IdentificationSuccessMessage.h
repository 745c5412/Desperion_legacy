#ifndef __IDENTIFICATION_SUCCESS_MESSAGE__
#define __IDENTIFICATION_SUCCESS_MESSAGE__

class IdentificationSuccessMessage : public DofusMessage
{
public:
	uint32 GetOpcode() const
	{ return SMSG_IDENTIFICATION_SUCCESS; }

	IdentificationSuccessMessage(int level, bool alreadyConnected, std::string pseudo, int guid, std::string question, time_t subscribeTime)
	{
		uint8 flag = 0;
		Desperion::BooleanByteWrapper::SetFlag(flag, 0, level > 0);
		Desperion::BooleanByteWrapper::SetFlag(flag, 1, alreadyConnected);
		m_buffer<<flag<<pseudo<<guid;
		m_buffer<<uint8(0)<<question<<uint64(subscribeTime * 1000);
	}
};

#endif