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

#ifndef __FRIEND_SPOUSE_INFORMATIONS__
#define __FRIEND_SPOUSE_INFORMATIONS__

class FriendSpouseInformations : public DofusModel
{
public:
	int spouseAccountId;
	int spouseId;
	std::string spouseName;
	uint8 spouseLevel;
	int8 breed;
	int8 sex;
	EntityLookPtr spouseEntityLook;
	BasicGuildInformationsPtr guildInfo;
	int8 alignmentSide;

	uint16 GetProtocol() const
	{ return FRIEND_SPOUSE_INFORMATIONS; }

	FriendSpouseInformations()
	{
	}

	FriendSpouseInformations(int spouseAccountId, int spouseId, std::string spouseName, uint8 spouseLevel, int8 breed, int8 sex, EntityLook* spouseEntityLook, BasicGuildInformations* guildInfo, int8 alignmentSide) : spouseAccountId(spouseAccountId), spouseId(spouseId), spouseName(spouseName), spouseLevel(spouseLevel), breed(breed), sex(sex), spouseEntityLook(spouseEntityLook), guildInfo(guildInfo), alignmentSide(alignmentSide)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<spouseAccountId<<spouseId<<spouseName<<spouseLevel<<breed<<sex;
		spouseEntityLook->Serialize(data);
		guildInfo->Serialize(data);
		data<<alignmentSide;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>spouseAccountId>>spouseId>>spouseName>>spouseLevel>>breed>>sex;
		spouseEntityLook.reset(new EntityLook);
		spouseEntityLook->Deserialize(data);
		guildInfo.reset(new BasicGuildInformations);
		guildInfo->Deserialize(data);
		data>>alignmentSide;
	}
};

typedef boost::shared_ptr<FriendSpouseInformations> FriendSpouseInformationsPtr;

#endif