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

#ifndef __GAME_FIGHT_RESUME_MESSAGE__
#define __GAME_FIGHT_RESUME_MESSAGE__

class GameFightResumeMessage : public GameFightSpectateMessage
{
public:
	std::vector<GameFightSpellCooldownPtr> spellCooldowns;
	int8 summonCount;
	int8 bombCount;

	uint16 GetOpcode() const
	{ return SMSG_GAME_FIGHT_RESUME; }

	GameFightResumeMessage()
	{
	}

	GameFightResumeMessage(std::vector<FightDispellableEffectExtendedInformationsPtr>& effects, std::vector<GameActionMarkPtr>& marks, int16 gameTurn, std::vector<GameFightSpellCooldownPtr>& spellCooldowns, int8 summonCount, int8 bombCount) : GameFightSpectateMessage(effects, marks, gameTurn), spellCooldowns(spellCooldowns), summonCount(summonCount), bombCount(bombCount)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		GameFightSpectateMessage::Serialize(data);
		uint16 size = spellCooldowns.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			spellCooldowns[a]->Serialize(data);
		data<<summonCount<<bombCount;
	}

	void Deserialize(ByteBuffer& data)
	{
		GameFightSpectateMessage::Deserialize(data);
		spellCooldowns.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			GameFightSpellCooldownPtr model(new GameFightSpellCooldown);
			model->Deserialize(data);
			spellCooldowns.push_back(model);
		}
		data>>summonCount>>bombCount;
	}
};

#endif