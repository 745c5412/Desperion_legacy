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

#ifndef __GAME_ROLE_PLAY_NAMED_ACTOR_INFORMATIONS__
#define __GAME_ROLE_PLAY_NAMED_ACTOR_INFORMATIONS__

class GameRolePlayNamedActorInformations : public GameRolePlayActorInformations
{
public:
	std::string name;

	uint16 GetProtocol() const
	{ return GAME_ROLE_PLAY_NAMED_ACTOR_INFORMATIONS; }

	GameRolePlayNamedActorInformations()
	{
	}

	GameRolePlayNamedActorInformations(int contextualId, EntityLook* look, EntityDispositionInformations* disposition, std::string name) : GameRolePlayActorInformations(contextualId, look, disposition), name(name)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		GameRolePlayActorInformations::Serialize(data);
		data<<name;
	}

	void Deserialize(ByteBuffer& data)
	{
		GameRolePlayActorInformations::Deserialize(data);
		data>>name;
	}
};

typedef boost::shared_ptr<GameRolePlayNamedActorInformations> GameRolePlayNamedActorInformationsPtr;

#endif