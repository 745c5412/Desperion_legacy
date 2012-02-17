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

#ifndef __GAME_FIGHT_PLACEMENT_POSSIBLE_POSITIONS_MESSAGE__
#define __GAME_FIGHT_PLACEMENT_POSSIBLE_POSITIONS_MESSAGE__

class GameFightPlacementPossiblePositionsMessage : public DofusMessage
{
public:
	std::vector<int16> positionsForChallengers, positionsForDefenders;
	int8 teamNumber;
	
	uint16 GetOpcode() const
	{ return SMSG_GAME_FIGHT_PLACEMENT_POSSIBLE_POSITIONS; }
	
	GameFightPlacementPossiblePositionsMessage()
	{
	}
	
	GameFightPlacementPossiblePositionsMessage(std::vector<int16>& positionsForChallengers, std::vector<int16>& positionsForDefenders,
		int8 teamNumber) : positionsForChallengers(positionsForChallengers), positionsForDefenders(positionsForDefenders), teamNumber(teamNumber)
	{
	}
	
	void Serialize(ByteBuffer& data) const
	{
		uint16 size = positionsForChallengers.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<positionsForChallengers[a];
		size = positionsForDefenders.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<positionsForDefenders[a];
		data<<teamNumber;
	}
	
	void Deserialize(ByteBuffer& data)
	{
		uint16 size;
		data>>size;
		positionsForChallengers.clear();
		for(uint16 a = 0; a < size; ++a)
		{
			int16 cell;
			data>>cell;
			positionsForChallengers.push_back(cell);
		}
		data>>size;
		positionsForDefenders.clear();
		for(uint16 a = 0; a < size; ++a)
		{
			int16 cell;
			data>>cell;
			positionsForDefenders.push_back(cell);
		}
		data>>teamNumber;
	}
};

#endif