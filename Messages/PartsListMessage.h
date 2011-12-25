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

#ifndef __PARTS_LIST_MESSAGE__
#define __PARTS_LIST_MESSAGE__

class PartsListMessage : public DofusMessage
{
public:
	std::vector<ContentPartPtr> parts;

	uint16 GetOpcode() const
	{ return SMSG_PARTS_LIST; }

	PartsListMessage()
	{
	}

	PartsListMessage(std::vector<ContentPartPtr>& parts) : parts(parts)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		uint16 size = parts.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			parts[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		parts.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			ContentPartPtr model(new ContentPart);
			model->Deserialize(data);
			parts.push_back(model);
		}
	}
};

#endif