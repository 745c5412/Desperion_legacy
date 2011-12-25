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

#ifndef __GAME_FIGHT_SYNCHRONIZE_MESSAGE__
#define __GAME_FIGHT_SYNCHRONIZE_MESSAGE__

class GameFightSynchronizeMessage : public DofusMessage
{
public:
	std::vector<GameFightFighterInformationsPtr> fighters;

	uint16 GetOpcode() const
	{ return SMSG_GAME_FIGHT_SYNCHRONIZE; }

	GameFightSynchronizeMessage()
	{
	}

	GameFightSynchronizeMessage(std::vector<GameFightFighterInformationsPtr>& fighters) : fighters(fighters)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		uint16 size = fighters.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
		{
			data<<fighters[a]->GetProtocol();
			fighters[a]->Serialize(data);
		}
	}

	void Deserialize(ByteBuffer& data)
	{
		fighters.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			uint16 protocol;
			data>>protocol;
			GameFightFighterInformationsPtr model(Desperion::ProtocolTypeManager::GetGameFightFighterInformations(protocol));
			model->Deserialize(data);
			fighters.push_back(model);
		}
	}
};

#endif