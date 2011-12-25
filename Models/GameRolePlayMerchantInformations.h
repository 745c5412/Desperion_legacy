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

#ifndef __GAME_ROLE_PLAY_MERCHANT_INFORMATIONS__
#define __GAME_ROLE_PLAY_MERCHANT_INFORMATIONS__

class GameRolePlayMerchantInformations : public GameRolePlayNamedActorInformations
{
public:
	int sellType;

	uint16 GetProtocol() const
	{ return GAME_ROLE_PLAY_MERCHANT_INFORMATIONS; }

	GameRolePlayMerchantInformations()
	{
	}

	GameRolePlayMerchantInformations(int contextualId, EntityLook* look, EntityDispositionInformations* disposition, std::string name, int sellType) : GameRolePlayNamedActorInformations(contextualId, look, disposition, name), sellType(sellType)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		GameRolePlayNamedActorInformations::Serialize(data);
		data<<sellType;
	}

	void Deserialize(ByteBuffer& data)
	{
		GameRolePlayNamedActorInformations::Deserialize(data);
		data>>sellType;
	}
};

typedef boost::shared_ptr<GameRolePlayMerchantInformations> GameRolePlayMerchantInformationsPtr;

#endif