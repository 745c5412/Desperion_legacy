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

#ifndef __PADDOCK_ABANDONNED_INFORMATIONS__
#define __PADDOCK_ABANDONNED_INFORMATIONS__

class PaddockAbandonnedInformations : public PaddockBuyableInformations
{
public:
	int guildId;

	uint16 GetProtocol() const
	{ return PADDOCK_ABANDONNED_INFORMATIONS; }

	PaddockAbandonnedInformations()
	{
	}

	PaddockAbandonnedInformations(int16 maxOutdoorMount, int16 maxItems, int price, bool locked, int guildId) : PaddockBuyableInformations(maxOutdoorMount, maxItems, price, locked), guildId(guildId)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		PaddockBuyableInformations::Serialize(data);
		data<<guildId;
	}

	void Deserialize(ByteBuffer& data)
	{
		PaddockBuyableInformations::Deserialize(data);
		data>>guildId;
	}
};

typedef boost::shared_ptr<PaddockAbandonnedInformations> PaddockAbandonnedInformationsPtr;

#endif