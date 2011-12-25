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

#ifndef __GAME_MAP_CHANGE_ORIENTATIONS_MESSAGE__
#define __GAME_MAP_CHANGE_ORIENTATIONS_MESSAGE__

class GameMapChangeOrientationsMessage : public DofusMessage
{
public:
	std::vector<ActorOrientationPtr> orientations;

	uint16 GetOpcode() const
	{ return SMSG_GAME_MAP_CHANGE_ORIENTATIONS; }

	GameMapChangeOrientationsMessage()
	{
	}

	GameMapChangeOrientationsMessage(std::vector<ActorOrientationPtr>& orientations) : orientations(orientations)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		uint16 size = orientations.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			orientations[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		orientations.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			ActorOrientationPtr model(new ActorOrientation);
			model->Deserialize(data);
			orientations.push_back(model);
		}
	}
};

#endif