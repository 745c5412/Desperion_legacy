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

#ifndef __PRISM_SUB_AREA_INFORMATION__
#define __PRISM_SUB_AREA_INFORMATION__

class PrismSubAreaInformation : public DofusModel
{
public:
	int16 worldX;
	int16 worldY;
	int mapId;
	int16 subAreaId;
	int8 alignment;
	bool isInFight;
	bool isFightable;

	uint16 GetProtocol() const
	{ return PRISM_SUB_AREA_INFORMATION; }

	PrismSubAreaInformation()
	{
	}

	PrismSubAreaInformation(int16 worldX, int16 worldY, int mapId, int16 subAreaId, int8 alignment, bool isInFight, bool isFightable) : worldX(worldX), worldY(worldY), mapId(mapId), subAreaId(subAreaId), alignment(alignment), isInFight(isInFight), isFightable(isFightable)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<worldX<<worldY<<mapId<<subAreaId<<alignment<<isInFight<<isFightable;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>worldX>>worldY>>mapId>>subAreaId>>alignment>>isInFight>>isFightable;
	}
};

typedef boost::shared_ptr<PrismSubAreaInformation> PrismSubAreaInformationPtr;

#endif