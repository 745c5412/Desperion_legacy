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

#ifndef __PADDOCK_INFORMATIONS_FOR_SELL__
#define __PADDOCK_INFORMATIONS_FOR_SELL__

class PaddockInformationsForSell : public DofusModel
{
public:
	std::string guildOwner;
	int16 worldX;
	int16 worldY;
	int16 subAreaId;
	int8 nbMount;
	int8 nbObject;
	int price;

	uint16 GetProtocol() const
	{ return PADDOCK_INFORMATIONS_FOR_SELL; }

	PaddockInformationsForSell()
	{
	}

	PaddockInformationsForSell(std::string guildOwner, int16 worldX, int16 worldY, int16 subAreaId, int8 nbMount, int8 nbObject, int price) : guildOwner(guildOwner), worldX(worldX), worldY(worldY), subAreaId(subAreaId), nbMount(nbMount), nbObject(nbObject), price(price)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<guildOwner<<worldX<<worldY<<subAreaId<<nbMount<<nbObject<<price;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>guildOwner>>worldX>>worldY>>subAreaId>>nbMount>>nbObject>>price;
	}
};

typedef boost::shared_ptr<PaddockInformationsForSell> PaddockInformationsForSellPtr;

#endif