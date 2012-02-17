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

#ifndef __MAP_NPCS_QUEST_STATUS_UPDATE_MESSAGE__
#define __MAP_NPCS_QUEST_STATUS_UPDATE_MESSAGE__

class MapNpcsQuestStatusUpdateMessage : public DofusMessage
{
public:
	int mapId;
	std::vector<int> npcsIdsWithQuest;
	std::vector<GameRolePlayNpcQuestFlagPtr> questFlags;
	std::vector<int> npcsIdsWithoutQuest;

	uint16 GetOpcode() const
	{ return SMSG_MAP_NPCS_QUEST_STATUS_UPDATE; }

	MapNpcsQuestStatusUpdateMessage()
	{
	}

	MapNpcsQuestStatusUpdateMessage(int mapId, std::vector<int>& npcsIdsWithQuest, std::vector<GameRolePlayNpcQuestFlagPtr>& questFlags, std::vector<int>& npcsIdsWithoutQuest) : mapId(mapId), npcsIdsWithQuest(npcsIdsWithQuest), questFlags(questFlags), npcsIdsWithoutQuest(npcsIdsWithoutQuest)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<mapId;
		uint16 size = npcsIdsWithQuest.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<npcsIdsWithQuest[a];
		uint16 size = questFlags.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			questFlags[a]->Serialize(data);
		uint16 size = npcsIdsWithoutQuest.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<npcsIdsWithoutQuest[a];
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>mapId;
		npcsIdsWithQuest.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int val;
			data>>val;
			npcsIdsWithQuest.push_back(val);
		}
		questFlags.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			GameRolePlayNpcQuestFlagPtr model(new GameRolePlayNpcQuestFlag);
			model->Deserialize(data);
			questFlags.push_back(model);
		}
		npcsIdsWithoutQuest.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int val;
			data>>val;
			npcsIdsWithoutQuest.push_back(val);
		}
	}
};

#endif