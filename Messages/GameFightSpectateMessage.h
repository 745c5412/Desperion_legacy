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

#ifndef __GAME_FIGHT_SPECTATE_MESSAGE__
#define __GAME_FIGHT_SPECTATE_MESSAGE__

class GameFightSpectateMessage : public DofusMessage
{
public:
	std::vector<FightDispellableEffectExtendedInformationsPtr> effects;
	std::vector<GameActionMarkPtr> marks;
	int16 gameTurn;

	uint16 GetOpcode() const
	{ return SMSG_GAME_FIGHT_SPECTATE; }

	GameFightSpectateMessage()
	{
	}

	GameFightSpectateMessage(std::vector<FightDispellableEffectExtendedInformationsPtr>& effects, std::vector<GameActionMarkPtr>& marks, int16 gameTurn) : effects(effects), marks(marks), gameTurn(gameTurn)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		uint16 size = effects.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
		{
			data<<effects[a]->GetProtocol();
			effects[a]->Serialize(data);
		}
		uint16 size = marks.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			marks[a]->Serialize(data);
		data<<gameTurn;
	}

	void Deserialize(ByteBuffer& data)
	{
		effects.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			uint16 protocol;
			data>>protocol;
			FightDispellableEffectExtendedInformationsPtr model(Desperion::ProtocolTypeManager::GetFightDispellableEffectExtendedInformations(protocol));
			model->Deserialize(data);
			effects.push_back(model);
		}
		marks.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			GameActionMarkPtr model(new GameActionMark);
			model->Deserialize(data);
			marks.push_back(model);
		}
		data>>gameTurn;
	}
};

#endif