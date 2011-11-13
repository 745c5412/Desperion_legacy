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

#ifndef __MAP_COMPLEMENTARY_INFORMATIONS_DATA_MESSAGE__
#define __MAP_COMPLEMENTARY_INFORMATIONS_DATA_MESSAGE__

class MapComplementaryInformationsDataMessage : public DofusMessage
{
public:
	int16 subareaId;
	int mapId;
	int8 subareaAlignmentSide;
	std::vector<GameRolePlayActorInformationsPtr> actors;

	virtual uint16 GetOpcode() const
	{ return SMSG_MAP_COMPLEMENTARY_INFORMATIONS_DATA; }

	MapComplementaryInformationsDataMessage()
	{
	}

	MapComplementaryInformationsDataMessage(int16 subareaId, int mapId, int8 subareaAlignmentSide /*, vector<HouseInformations> */,
		std::list<DisplayableEntity*>& actors /*, vector<InteractiveElement>, vector<StatedElement>, vector<MapObstacle>,
													  vector<FightCommonInformations>*/) : subareaId(subareaId),
		mapId(mapId), subareaAlignmentSide(subareaAlignmentSide)
	{
		for(std::list<DisplayableEntity*>::iterator it = actors.begin(); it != actors.end(); ++it)
		{
			GameRolePlayActorInformationsPtr rp((*it)->ToActor());
			this->actors.push_back(rp);
		}
	}

	void Serialize(ByteBuffer& data)
	{
		data<<subareaId<<mapId<<subareaAlignmentSide;
		data<<uint16(0); // sizeof(vector<HouseInformations>)
		uint16 size = actors.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
		{
			data<<actors[a]->GetProtocol();
			actors[a]->Serialize(data);
		}
		data<<uint16(0); // sizeof(vector<InteractiveElement>)
		data<<uint16(0); // sizeof(vector<StatedElement>)
		data<<uint16(0); // sizeof(vector<MapObstacles>)
		data<<uint16(0); // sizeof(vector<FightCommonInformations>)
	}

	void Deserialize(ByteBuffer& data)
	{
		actors.clear();
		data>>subareaId>>mapId>>subareaAlignmentSide;
		uint16 size;
		data>>size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			uint16 protocol;
			data>>protocol;
			GameRolePlayActorInformationsPtr rp(Desperion::ProtocolTypeManager::GetGameRolePlayActorInformations(protocol));
			actors.push_back(rp);
		}
		data>>size;
		data>>size;
		data>>size;
		data>>size;
	}
};

#endif