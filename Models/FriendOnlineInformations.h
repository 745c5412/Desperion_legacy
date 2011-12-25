/*
	This file is part of Desperion.
	Copyright 2010, 2011 LittleScaraby, Nekkro

	Desperion is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Desperion is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Desperion.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __FRIEND_ONLINE_INFORMATIONS__
#define __FRIEND_ONLINE_INFORMATIONS__

class FriendOnlineInformations : public FriendInformations
{
public:
	std::string playerName;
	int16 level;
	int8 alignmentSide;
	int8 breed;
	bool sex;
	BasicGuildInformationsPtr guildInfo;
	int8 moodSmileyId;

	uint16 GetProtocol() const
	{ return FRIEND_ONLINE_INFORMATIONS; }

	FriendOnlineInformations()
	{
	}

	FriendOnlineInformations(int accountId, std::string accountName, int8 playerState, int lastConnection, std::string playerName, int16 level, int8 alignmentSide, int8 breed, bool sex, BasicGuildInformations* guildInfo, int8 moodSmileyId) : FriendInformations(accountId, accountName, playerState, lastConnection), playerName(playerName), level(level), alignmentSide(alignmentSide), breed(breed), sex(sex), guildInfo(guildInfo), moodSmileyId(moodSmileyId)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		FriendInformations::Serialize(data);
		data<<playerName<<level<<alignmentSide<<breed<<sex;
		guildInfo->Serialize(data);
		data<<moodSmileyId;
	}

	void Deserialize(ByteBuffer& data)
	{
		FriendInformations::Deserialize(data);
		data>>playerName>>level>>alignmentSide>>breed>>sex;
		guildInfo.reset(new BasicGuildInformations);
		guildInfo->Deserialize(data);
		data>>moodSmileyId;
	}
};

typedef boost::shared_ptr<FriendOnlineInformations> FriendOnlineInformationsPtr;

#endif