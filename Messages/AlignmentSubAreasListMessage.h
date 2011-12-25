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

#ifndef __ALIGNMENT_SUB_AREAS_LIST_MESSAGE__
#define __ALIGNMENT_SUB_AREAS_LIST_MESSAGE__

class AlignmentSubAreasListMessage : public DofusMessage
{
public:
	std::vector<int16> angelsSubAreas;
	std::vector<int16> evilsSubAreas;

	uint16 GetOpcode() const
	{ return SMSG_ALIGNMENT_SUB_AREAS_LIST; }

	AlignmentSubAreasListMessage()
	{
	}

	AlignmentSubAreasListMessage(std::vector<int16>& angelsSubAreas, std::vector<int16>& evilsSubAreas) : angelsSubAreas(angelsSubAreas), evilsSubAreas(evilsSubAreas)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		uint16 size = angelsSubAreas.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<angelsSubAreas[a];
		uint16 size = evilsSubAreas.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<evilsSubAreas[a];
	}

	void Deserialize(ByteBuffer& data)
	{
		angelsSubAreas.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int16 val;
			data>>val;
			angelsSubAreas.push_back(val);
		}
		evilsSubAreas.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int16 val;
			data>>val;
			evilsSubAreas.push_back(val);
		}
	}
};

#endif