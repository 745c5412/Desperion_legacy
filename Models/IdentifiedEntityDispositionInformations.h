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

#ifndef __IDENTIFIED_ENTITY_DISPOSITION_INFORMATIONS__
#define __IDENTIFIED_ENTITY_DISPOSITION_INFORMATIONS__

class IdentifiedEntityDispositionInformations : public EntityDispositionInformations
{
public:
	int id;

	uint16 GetProtocol() const
	{ return IDENTIFIED_ENTITY_DISPOSITION_INFORMATIONS; }

	IdentifiedEntityDispositionInformations()
	{
	}

	IdentifiedEntityDispositionInformations(int16 cellId, int8 direction, int id) : EntityDispositionInformations(cellId, direction), id(id)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		EntityDispositionInformations::Serialize(data);
		data<<id;
	}

	void Deserialize(ByteBuffer& data)
	{
		EntityDispositionInformations::Deserialize(data);
		data>>id;
	}
};

typedef boost::shared_ptr<IdentifiedEntityDispositionInformations> IdentifiedEntityDispositionInformationsPtr;

#endif