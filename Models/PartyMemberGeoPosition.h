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

#ifndef __PARTY_MEMBER_GEO_POSITION__
#define __PARTY_MEMBER_GEO_POSITION__

class PartyMemberGeoPosition : public DofusModel
{
public:
	int memberId;
	int16 worldX;
	int16 worldY;
	int mapId;
	int16 subAreaId;

	uint16 GetProtocol() const
	{ return PARTY_MEMBER_GEO_POSITION; }

	PartyMemberGeoPosition()
	{
	}

	PartyMemberGeoPosition(int memberId, int16 worldX, int16 worldY, int mapId, int16 subAreaId) : memberId(memberId), worldX(worldX), worldY(worldY), mapId(mapId), subAreaId(subAreaId)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<memberId<<worldX<<worldY<<mapId<<subAreaId;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>memberId>>worldX>>worldY>>mapId>>subAreaId;
	}
};

typedef boost::shared_ptr<PartyMemberGeoPosition> PartyMemberGeoPositionPtr;

#endif