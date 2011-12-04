#ifndef __FRIEND_ONLINE_INFORMATIONS__
#define __FRIEND_ONLINE_INFORMATIONS__

class FriendOnlineInformations : public FriendInformations
{
public:
	std::string playerName;
	int16 level;
	int8 alignmentSide, breed, moodSmileyId;
	bool sex;

	virtual uint16 GetProtocol() const
	{ return FRIEND_ONLINE_INFORMATIONS; }

	FriendOnlineInformations()
	{
	}

	FriendOnlineInformations(int accountId, std::string accountName, int8 playerState, int lastConnection,
		std::string playerName, int16 level, int8 alignmentSide, int8 breed, bool sex, int8 moodSmileyId)
		: FriendInformations(accountId, accountName, playerState, lastConnection), playerName(playerName),
		level(level), alignmentSide(alignmentSide), breed(breed), sex(sex), moodSmileyId(moodSmileyId)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		FriendInformations::Serialize(data);
		data<<playerName<<level<<alignmentSide<<breed<<sex;
		data<<int(0)<<"";
		data<<moodSmileyId;
	}

	void Deserialize(ByteBuffer& data)
	{
		FriendInformations::Deserialize(data);
		data>>playerName>>level>>alignmentSide>>breed>>sex;
		int guildId;
		std::string guildName;
		data>>guildId>>guildName;
		data>>moodSmileyId;
	}
};

typedef boost::shared_ptr<FriendOnlineInformations> FriendOnlineInformationsPtr;

#endif