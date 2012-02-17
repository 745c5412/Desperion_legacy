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

#ifndef __CHARACTER_TO_RECOLOR_INFORMATION__
#define __CHARACTER_TO_RECOLOR_INFORMATION__

class CharacterToRecolorInformation : public DofusModel
{
public:
	int id;
	std::vector<int> colors;

	uint16 GetProtocol() const
	{ return CHARACTER_TO_RECOLOR_INFORMATION; }

	CharacterToRecolorInformation()
	{
	}

	CharacterToRecolorInformation(int id, std::vector<int>& colors) : id(id), colors(colors)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<id;
		uint16 size = colors.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<colors[a];
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>id;
		colors.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int val;
			data>>val;
			colors.push_back(val);
		}
	}
};

typedef boost::shared_ptr<CharacterToRecolorInformation> CharacterToRecolorInformationPtr;

#endif