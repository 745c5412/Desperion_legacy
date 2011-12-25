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

#ifndef __GAME_CONTEXT_MOVE_MULTIPLE_ELEMENTS_MESSAGE__
#define __GAME_CONTEXT_MOVE_MULTIPLE_ELEMENTS_MESSAGE__

class GameContextMoveMultipleElementsMessage : public DofusMessage
{
public:
	std::vector<EntityMovementInformationsPtr> movements;

	uint16 GetOpcode() const
	{ return SMSG_GAME_CONTEXT_MOVE_MULTIPLE_ELEMENTS; }

	GameContextMoveMultipleElementsMessage()
	{
	}

	GameContextMoveMultipleElementsMessage(std::vector<EntityMovementInformationsPtr>& movements) : movements(movements)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		uint16 size = movements.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			movements[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		movements.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			EntityMovementInformationsPtr model(new EntityMovementInformations);
			model->Deserialize(data);
			movements.push_back(model);
		}
	}
};

#endif