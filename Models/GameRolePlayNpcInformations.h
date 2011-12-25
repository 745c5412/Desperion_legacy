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

#ifndef __GAME_ROLE_PLAY_NPC_INFORMATIONS__
#define __GAME_ROLE_PLAY_NPC_INFORMATIONS__

class GameRolePlayNpcInformations : public GameRolePlayActorInformations
{
public:
	int16 npcId;
	bool sex;
	int16 specialArtworkId;

	uint16 GetProtocol() const
	{ return GAME_ROLE_PLAY_NPC_INFORMATIONS; }

	GameRolePlayNpcInformations()
	{
	}

	GameRolePlayNpcInformations(int contextualId, EntityLook* look, EntityDispositionInformations* disposition, int16 npcId, bool sex, int16 specialArtworkId) : GameRolePlayActorInformations(contextualId, look, disposition), npcId(npcId), sex(sex), specialArtworkId(specialArtworkId)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		GameRolePlayActorInformations::Serialize(data);
		data<<npcId<<sex<<specialArtworkId;
	}

	void Deserialize(ByteBuffer& data)
	{
		GameRolePlayActorInformations::Deserialize(data);
		data>>npcId>>sex>>specialArtworkId;
	}
};

typedef boost::shared_ptr<GameRolePlayNpcInformations> GameRolePlayNpcInformationsPtr;

#endif