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

#ifndef __FRIEND_SPOUSE_ONLINE_INFORMATIONS__
#define __FRIEND_SPOUSE_ONLINE_INFORMATIONS__

class FriendSpouseOnlineInformations : public FriendSpouseInformations
{
public:
	bool inFight;
	bool followSpouse;
	bool pvpEnabled;
	int mapId;
	int16 subAreaId;

	uint16 GetProtocol() const
	{ return FRIEND_SPOUSE_ONLINE_INFORMATIONS; }

	FriendSpouseOnlineInformations()
	{
	}

	FriendSpouseOnlineInformations(int spouseAccountId, int spouseId, std::string spouseName, uint8 spouseLevel, int8 breed, int8 sex, EntityLook* spouseEntityLook, BasicGuildInformations* guildInfo, int8 alignmentSide, bool inFight, bool followSpouse, bool pvpEnabled, int mapId, int16 subAreaId) : FriendSpouseInformations(spouseAccountId, spouseId, spouseName, spouseLevel, breed, sex, spouseEntityLook, guildInfo, alignmentSide), inFight(inFight), followSpouse(followSpouse), pvpEnabled(pvpEnabled), mapId(mapId), subAreaId(subAreaId)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		FriendSpouseInformations::Serialize(data);
		int8 b = 0;
		BooleanByteWrapper::SetFlag(b, 0, inFight);
		BooleanByteWrapper::SetFlag(b, 1, followSpouse);
		BooleanByteWrapper::SetFlag(b, 2, pvpEnabled);
		data<<b<<mapId<<subAreaId;
	}

	void Deserialize(ByteBuffer& data)
	{
		FriendSpouseInformations::Deserialize(data);
		int8 b;
		data>>b;
		inFight = BooleanByteWrapper::GetFlag(b, 0);
		followSpouse = BooleanByteWrapper::GetFlag(b, 1);
		pvpEnabled = BooleanByteWrapper::GetFlag(b, 2);
		data>>mapId>>subAreaId;
	}
};

typedef boost::shared_ptr<FriendSpouseOnlineInformations> FriendSpouseOnlineInformationsPtr;

#endif