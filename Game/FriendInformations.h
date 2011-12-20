#ifndef __FRIEND_INFORMATIONS__
#define __FRIEND_INFORMATIONS__

class FriendInformations : public AbstractContactInformations
{
public:
	int8 playerState;
	int lastConnection;

	virtual uint16 GetProtocol() const
	{ return FRIEND_INFORMATIONS; }

	FriendInformations()
	{
	}

	FriendInformations(int accountId, std::string accountName, int8 playerState, int lastConnection)
		: AbstractContactInformations(accountId, accountName), playerState(playerState), lastConnection(lastConnection)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		AbstractContactInformations::Serialize(data);
		data<<playerState<<lastConnection;
	}

	void Deserialize(ByteBuffer& data)
	{
		AbstractContactInformations::Deserialize(data);
		data>>playerState>>lastConnection;
	}
};

typedef boost::shared_ptr<FriendInformations> FriendInformationsPtr;

#endif