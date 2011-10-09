#ifndef __ACQUAINTANCE_SEARCH_MESSAGE__
#define __ACQUAINTANCE_SEARCH_MESSAGE__

class AcquaintanceSearchMessage : public DofusMessage
{
public:
	std::string nickName;

	uint32 GetOpcode() const
	{ return CMSG_ACQUAINTANCE_SEARCH; }

	AcquaintanceSearchMessage(ByteBuffer& data)
	{
		data>>nickName;
	}
};

#endif