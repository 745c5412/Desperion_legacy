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

#ifndef __NPC_STATIC_INFORMATIONS__
#define __NPC_STATIC_INFORMATIONS__

class NpcStaticInformations : public DofusModel
{
public:
	int16 npcId;
	bool sex;
	int16 specialArtworkId;

	uint16 GetProtocol() const
	{ return NPC_STATIC_INFORMATIONS; }

	NpcStaticInformations()
	{
	}

	NpcStaticInformations(int16 npcId, bool sex, int16 specialArtworkId) : npcId(npcId), sex(sex), specialArtworkId(specialArtworkId)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<npcId<<sex<<specialArtworkId;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>npcId>>sex>>specialArtworkId;
	}
};

typedef boost::shared_ptr<NpcStaticInformations> NpcStaticInformationsPtr;

#endif