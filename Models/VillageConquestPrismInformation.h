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

#ifndef __VILLAGE_CONQUEST_PRISM_INFORMATION__
#define __VILLAGE_CONQUEST_PRISM_INFORMATION__

class VillageConquestPrismInformation : public DofusModel
{
public:
	bool isEntered;
	bool isInRoom;
	int16 areaId;
	int8 areaAlignment;

	uint16 GetProtocol() const
	{ return VILLAGE_CONQUEST_PRISM_INFORMATION; }

	VillageConquestPrismInformation()
	{
	}

	VillageConquestPrismInformation(bool isEntered, bool isInRoom, int16 areaId, int8 areaAlignment) : isEntered(isEntered), isInRoom(isInRoom), areaId(areaId), areaAlignment(areaAlignment)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		int8 b = 0;
		BooleanByteWrapper::SetFlag(b, 0, isEntered);
		BooleanByteWrapper::SetFlag(b, 1, isInRoom);
		data<<b<<areaId<<areaAlignment;
	}

	void Deserialize(ByteBuffer& data)
	{
		int8 b;
		data>>b;
		isEntered = BooleanByteWrapper::GetFlag(b, 0);
		isInRoom = BooleanByteWrapper::GetFlag(b, 1);
		data>>areaId>>areaAlignment;
	}
};

typedef boost::shared_ptr<VillageConquestPrismInformation> VillageConquestPrismInformationPtr;

#endif