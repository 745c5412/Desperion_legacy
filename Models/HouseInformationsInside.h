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

#ifndef __HOUSE_INFORMATIONS_INSIDE__
#define __HOUSE_INFORMATIONS_INSIDE__

class HouseInformationsInside : public DofusModel
{
public:
	int houseId;
	int16 modelId;
	int ownerId;
	std::string ownerName;
	int16 worldX;
	int16 worldY;
	uint32 price;
	bool isLocked;

	uint16 GetProtocol() const
	{ return HOUSE_INFORMATIONS_INSIDE; }

	HouseInformationsInside()
	{
	}

	HouseInformationsInside(int houseId, int16 modelId, int ownerId, std::string ownerName, int16 worldX, int16 worldY, uint32 price, bool isLocked) : houseId(houseId), modelId(modelId), ownerId(ownerId), ownerName(ownerName), worldX(worldX), worldY(worldY), price(price), isLocked(isLocked)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<houseId<<modelId<<ownerId<<ownerName<<worldX<<worldY<<price<<isLocked;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>houseId>>modelId>>ownerId>>ownerName>>worldX>>worldY>>price>>isLocked;
	}
};

typedef boost::shared_ptr<HouseInformationsInside> HouseInformationsInsidePtr;

#endif