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

#ifndef __NPC_GENERIC_ACTION_REQUEST_MESSAGE__
#define __NPC_GENERIC_ACTION_REQUEST_MESSAGE__

class NpcGenericActionRequestMessage : public DofusMessage
{
public:
	int npcId;
	int8 npcActionId;
	int npcMapId;

	uint16 GetOpcode() const
	{ return CMSG_NPC_GENERIC_ACTION_REQUEST; }

	NpcGenericActionRequestMessage()
	{
	}

	NpcGenericActionRequestMessage(int npcId, int8 npcActionId, int npcMapId) : npcId(npcId), npcActionId(npcActionId), npcMapId(npcMapId)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<npcId<<npcActionId<<npcMapId;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>npcId>>npcActionId>>npcMapId;
	}
};

#endif