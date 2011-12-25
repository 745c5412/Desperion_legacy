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

#ifndef __GAME_FIGHT_TAX_COLLECTOR_INFORMATIONS__
#define __GAME_FIGHT_TAX_COLLECTOR_INFORMATIONS__

class GameFightTaxCollectorInformations : public GameFightAIInformations
{
public:
	int16 firstNameId;
	int16 lastNameId;
	int16 level;

	uint16 GetProtocol() const
	{ return GAME_FIGHT_TAX_COLLECTOR_INFORMATIONS; }

	GameFightTaxCollectorInformations()
	{
	}

	GameFightTaxCollectorInformations(int contextualId, EntityLook* look, EntityDispositionInformations* disposition, int8 teamId, bool alive, GameFightMinimalStats* stats, int16 firstNameId, int16 lastNameId, int16 level) : GameFightAIInformations(contextualId, look, disposition, teamId, alive, stats), firstNameId(firstNameId), lastNameId(lastNameId), level(level)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		GameFightAIInformations::Serialize(data);
		data<<firstNameId<<lastNameId<<level;
	}

	void Deserialize(ByteBuffer& data)
	{
		GameFightAIInformations::Deserialize(data);
		data>>firstNameId>>lastNameId>>level;
	}
};

typedef boost::shared_ptr<GameFightTaxCollectorInformations> GameFightTaxCollectorInformationsPtr;

#endif