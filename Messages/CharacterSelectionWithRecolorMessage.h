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

#ifndef __CHARACTER_SELECTION_WITH_RECOLOR_MESSAGE__
#define __CHARACTER_SELECTION_WITH_RECOLOR_MESSAGE__

class CharacterSelectionWithRecolorMessage : public CharacterSelectionMessage
{
public:
	std::vector<int> indexedColor;

	uint16 GetOpcode() const
	{ return CMSG_CHARACTER_SELECTION_WITH_RECOLOR; }

	CharacterSelectionWithRecolorMessage()
	{
	}

	CharacterSelectionWithRecolorMessage(int id, std::vector<int>& indexedColor) : CharacterSelectionMessage(id), indexedColor(indexedColor)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		CharacterSelectionMessage::Serialize(data);
		uint16 size = indexedColor.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<indexedColor[a];
	}

	void Deserialize(ByteBuffer& data)
	{
		CharacterSelectionMessage::Deserialize(data);
		indexedColor.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int val;
			data>>val;
			indexedColor.push_back(val);
		}
	}
};

#endif