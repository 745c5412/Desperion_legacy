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

#ifndef __OBJECT_GROUND_LIST_ADDED_MESSAGE__
#define __OBJECT_GROUND_LIST_ADDED_MESSAGE__

class ObjectGroundListAddedMessage : public DofusMessage
{
public:
	std::vector<int16> cells;
	std::vector<int> referenceIds;

	virtual uint16 GetOpcode() const
	{ return SMSG_OBJECT_GROUND_LIST_ADDED; }

	ObjectGroundListAddedMessage()
	{
	}

	ObjectGroundListAddedMessage(std::vector<int16>& cells, std::vector<int>& referenceIds) : cells(cells),
		referenceIds(referenceIds)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		uint16 size = cells.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<cells[a];
		size = referenceIds.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<referenceIds[a];
	}

	void Deserialize(ByteBuffer& data)
	{
		cells.clear();
		referenceIds.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int16 cell;
			data>>cell;
			cells.push_back(cell);
		}
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int ref;
			data>>ref;
			referenceIds.push_back(ref);
		}
	}
};

#endif