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

#ifndef __GAME_FIGHT_RESUME_WITH_SLAVES_MESSAGE__
#define __GAME_FIGHT_RESUME_WITH_SLAVES_MESSAGE__

class GameFightResumeWithSlavesMessage : public GameFightResumeMessage
{
public:
	std::vector<GameFightResumeSlaveInfoPtr> slavesInfo;

	uint16 GetOpcode() const
	{ return SMSG_GAME_FIGHT_RESUME_WITH_SLAVES; }

	GameFightResumeWithSlavesMessage()
	{
	}

	GameFightResumeWithSlavesMessage(std::vector<FightDispellableEffectExtendedInformationsPtr>& effects, std::vector<GameActionMarkPtr>& marks, int16 gameTurn, std::vector<GameFightSpellCooldownPtr>& spellCooldowns, int8 summonCount, int8 bombCount, std::vector<GameFightResumeSlaveInfoPtr>& slavesInfo) : GameFightResumeMessage(effects, marks, gameTurn, spellCooldowns, summonCount, bombCount), slavesInfo(slavesInfo)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		GameFightResumeMessage::Serialize(data);
		uint16 size = slavesInfo.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			slavesInfo[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		GameFightResumeMessage::Deserialize(data);
		slavesInfo.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			GameFightResumeSlaveInfoPtr model(new GameFightResumeSlaveInfo);
			model->Deserialize(data);
			slavesInfo.push_back(model);
		}
	}
};

#endif