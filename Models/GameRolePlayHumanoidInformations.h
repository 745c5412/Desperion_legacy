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

#ifndef __GAME_ROLE_PLAY_HUMANOID_INFORMATIONS__
#define __GAME_ROLE_PLAY_HUMANOID_INFORMATIONS__

class GameRolePlayHumanoidInformations : public GameRolePlayNamedActorInformations
{
public:
	HumanInformationsPtr humanoidInfo;

	uint16 GetProtocol() const
	{ return GAME_ROLE_PLAY_HUMANOID_INFORMATIONS; }

	GameRolePlayHumanoidInformations()
	{
	}

	GameRolePlayHumanoidInformations(int contextualId, EntityLook* look, EntityDispositionInformations* disposition, std::string name, HumanInformations* humanoidInfo) : GameRolePlayNamedActorInformations(contextualId, look, disposition, name), humanoidInfo(humanoidInfo)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		GameRolePlayNamedActorInformations::Serialize(data);
		data<<humanoidInfo->GetProtocol();
		humanoidInfo->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		GameRolePlayNamedActorInformations::Deserialize(data);
		uint16 protocol;
		data>>protocol;
		humanoidInfo.reset(Desperion::ProtocolTypeManager::GetHumanInformations(protocol));
		humanoidInfo->Deserialize(data);
	}
};

typedef boost::shared_ptr<GameRolePlayHumanoidInformations> GameRolePlayHumanoidInformationsPtr;

#endif