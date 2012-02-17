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

#ifndef __GAME_ACTION_MARK__
#define __GAME_ACTION_MARK__

class GameActionMark : public DofusModel
{
public:
	int markAuthorId;
	int markSpellId;
	int16 markId;
	int8 markType;
	std::vector<GameActionMarkedCellPtr> cells;

	uint16 GetProtocol() const
	{ return GAME_ACTION_MARK; }

	GameActionMark()
	{
	}

	GameActionMark(int markAuthorId, int markSpellId, int16 markId, int8 markType, std::vector<GameActionMarkedCellPtr>& cells) : markAuthorId(markAuthorId), markSpellId(markSpellId), markId(markId), markType(markType), cells(cells)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<markAuthorId<<markSpellId<<markId<<markType;
		uint16 size = cells.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			cells[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>markAuthorId>>markSpellId>>markId>>markType;
		cells.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			GameActionMarkedCellPtr model(new GameActionMarkedCell);
			model->Deserialize(data);
			cells.push_back(model);
		}
	}
};

typedef boost::shared_ptr<GameActionMark> GameActionMarkPtr;

#endif