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

#ifndef __TEXT_INFORMATION_MESSAGE__
#define __TEXT_INFORMATION_MESSAGE__

class TextInformationMessage : public DofusMessage
{
public:
	int8 type;
	int16 id;
	std::vector<std::string> params;

	virtual uint16 GetOpcode() const
	{ return SMSG_TEXT_INFORMATION; }

	TextInformationMessage()
	{
	}

	TextInformationMessage(int8 type, int16 id, std::vector<std::string>& params) : type(type),
		id(id), params(params)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<type<<id;
		uint16 size = params.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<params[a];
	}

	void Deserialize(ByteBuffer& data)
	{
		params.clear();
		data>>type>>id;
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			std::string param;
			data>>param;
			params.push_back(param);
		}
	}
};

#endif