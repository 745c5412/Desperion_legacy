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

#ifndef __GAME_ROLE_PLAY_MOUNT_INFORMATIONS__
#define __GAME_ROLE_PLAY_MOUNT_INFORMATIONS__

class GameRolePlayMountInformations : public GameRolePlayNamedActorInformations
{
public:
	std::string ownerName;
	uint8 level;

	uint16 GetProtocol() const
	{ return GAME_ROLE_PLAY_MOUNT_INFORMATIONS; }

	GameRolePlayMountInformations()
	{
	}

	GameRolePlayMountInformations(int contextualId, EntityLook* look, EntityDispositionInformations* disposition, std::string name, std::string ownerName, uint8 level) : GameRolePlayNamedActorInformations(contextualId, look, disposition, name), ownerName(ownerName), level(level)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		GameRolePlayNamedActorInformations::Serialize(data);
		data<<ownerName<<level;
	}

	void Deserialize(ByteBuffer& data)
	{
		GameRolePlayNamedActorInformations::Deserialize(data);
		data>>ownerName>>level;
	}
};

typedef boost::shared_ptr<GameRolePlayMountInformations> GameRolePlayMountInformationsPtr;

#endif