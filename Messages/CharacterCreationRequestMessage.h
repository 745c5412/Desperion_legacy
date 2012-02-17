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

#ifndef __CHARACTER_CREATION_REQUEST_MESSAGE__
#define __CHARACTER_CREATION_REQUEST_MESSAGE__

class CharacterCreationRequestMessage : public DofusMessage
{
public:
	std::string name;
	int8 breed;
	bool sex;
	std::vector<int> colors;

	virtual uint16 GetOpcode() const
	{ return CMSG_CHARACTER_CREATION_REQUEST; }

	CharacterCreationRequestMessage()
	{
	}

	CharacterCreationRequestMessage(std::string name, int8 breed, bool sex, std::vector<int>& colors) : name(name),
		breed(breed), sex(sex), colors(colors)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<name<<breed<<sex;
		for(uint16 a = 0; a < 5; ++a)
			data<<colors[a];
	}

	void Deserialize(ByteBuffer& data)
	{
		colors.clear();
		data>>name>>breed>>sex;
		for(uint16 a = 0; a < 5; ++a)
		{
			int color;
			data>>color;
			colors.push_back(color);
		}
	}
};

#endif