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

#ifndef __GAME_ROLE_PLAY_TAX_COLLECTOR_INFORMATIONS__
#define __GAME_ROLE_PLAY_TAX_COLLECTOR_INFORMATIONS__

class GameRolePlayTaxCollectorInformations : public GameRolePlayActorInformations
{
public:
	int16 firstNameId;
	int16 lastNameId;
	GuildInformationsPtr guildIdentity;
	uint8 guildLevel;
	int taxCollectorAttack;

	uint16 GetProtocol() const
	{ return GAME_ROLE_PLAY_TAX_COLLECTOR_INFORMATIONS; }

	GameRolePlayTaxCollectorInformations()
	{
	}

	GameRolePlayTaxCollectorInformations(int contextualId, EntityLook* look, EntityDispositionInformations* disposition, int16 firstNameId, int16 lastNameId, GuildInformations* guildIdentity, uint8 guildLevel, int taxCollectorAttack) : GameRolePlayActorInformations(contextualId, look, disposition), firstNameId(firstNameId), lastNameId(lastNameId), guildIdentity(guildIdentity), guildLevel(guildLevel), taxCollectorAttack(taxCollectorAttack)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		GameRolePlayActorInformations::Serialize(data);
		data<<firstNameId<<lastNameId;
		guildIdentity->Serialize(data);
		data<<guildLevel<<taxCollectorAttack;
	}

	void Deserialize(ByteBuffer& data)
	{
		GameRolePlayActorInformations::Deserialize(data);
		data>>firstNameId>>lastNameId;
		guildIdentity.reset(new GuildInformations);
		guildIdentity->Deserialize(data);
		data>>guildLevel>>taxCollectorAttack;
	}
};

typedef boost::shared_ptr<GameRolePlayTaxCollectorInformations> GameRolePlayTaxCollectorInformationsPtr;

#endif