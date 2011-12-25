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

#ifndef __ENTITY_MOVEMENT_INFORMATIONS__
#define __ENTITY_MOVEMENT_INFORMATIONS__

class EntityMovementInformations : public DofusModel
{
public:
	int id;
	std::vector<int8> steps;

	uint16 GetProtocol() const
	{ return ENTITY_MOVEMENT_INFORMATIONS; }

	EntityMovementInformations()
	{
	}

	EntityMovementInformations(int id, std::vector<int8>& steps) : id(id), steps(steps)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<id;
		uint16 size = steps.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<steps[a];
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>id;
		steps.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int8 val;
			data>>val;
			steps.push_back(val);
		}
	}
};

typedef boost::shared_ptr<EntityMovementInformations> EntityMovementInformationsPtr;

#endif