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

#ifndef __GUILD_PADDOCK_BOUGHT_MESSAGE__
#define __GUILD_PADDOCK_BOUGHT_MESSAGE__

class GuildPaddockBoughtMessage : public DofusMessage
{
public:
	int16 worldX;
	int16 worldY;
	int8 nbMountMax;
	int8 nbItemMax;

	uint16 GetOpcode() const
	{ return SMSG_GUILD_PADDOCK_BOUGHT; }

	GuildPaddockBoughtMessage()
	{
	}

	GuildPaddockBoughtMessage(int16 worldX, int16 worldY, int8 nbMountMax, int8 nbItemMax) : worldX(worldX), worldY(worldY), nbMountMax(nbMountMax), nbItemMax(nbItemMax)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<worldX<<worldY<<nbMountMax<<nbItemMax;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>worldX>>worldY>>nbMountMax>>nbItemMax;
	}
};

#endif