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

#ifndef __ENTITY_DISPOSITION_INFORMATIONS__
#define __ENTITY_DISPOSITION_INFORMATIONS__

class EntityDispositionInformations : public DofusModel
{
public:
	int16 cellId;
	int8 direction;

	uint16 GetProtocol() const
	{ return ENTITY_DISPOSITION_INFORMATIONS; }

	EntityDispositionInformations()
	{
	}

	EntityDispositionInformations(int16 cellId, int8 direction) : cellId(cellId), direction(direction)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<cellId<<direction;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>cellId>>direction;
	}
};

typedef boost::shared_ptr<EntityDispositionInformations> EntityDispositionInformationsPtr;

#endif