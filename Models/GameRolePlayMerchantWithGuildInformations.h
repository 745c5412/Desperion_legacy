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

#ifndef __GAME_ROLE_PLAY_MERCHANT_WITH_GUILD_INFORMATIONS__
#define __GAME_ROLE_PLAY_MERCHANT_WITH_GUILD_INFORMATIONS__

class GameRolePlayMerchantWithGuildInformations : public GameRolePlayMerchantInformations
{
public:
	GuildInformationsPtr guildInformations;

	uint16 GetProtocol() const
	{ return GAME_ROLE_PLAY_MERCHANT_WITH_GUILD_INFORMATIONS; }

	GameRolePlayMerchantWithGuildInformations()
	{
	}

	GameRolePlayMerchantWithGuildInformations(int contextualId, EntityLook* look, EntityDispositionInformations* disposition, std::string name, int sellType, GuildInformations* guildInformations) : GameRolePlayMerchantInformations(contextualId, look, disposition, name, sellType), guildInformations(guildInformations)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		GameRolePlayMerchantInformations::Serialize(data);
		guildInformations->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		GameRolePlayMerchantInformations::Deserialize(data);
		guildInformations.reset(new GuildInformations);
		guildInformations->Deserialize(data);
	}
};

typedef boost::shared_ptr<GameRolePlayMerchantWithGuildInformations> GameRolePlayMerchantWithGuildInformationsPtr;

#endif