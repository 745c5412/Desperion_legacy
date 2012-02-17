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

#ifndef __TAX_COLLECTOR_NAME__
#define __TAX_COLLECTOR_NAME__

class TaxCollectorName : public DofusModel
{
public:
	int16 firstNameId;
	int16 lastNameId;

	uint16 GetProtocol() const
	{ return TAX_COLLECTOR_NAME; }

	TaxCollectorName()
	{
	}

	TaxCollectorName(int16 firstNameId, int16 lastNameId) : firstNameId(firstNameId), lastNameId(lastNameId)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<firstNameId<<lastNameId;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>firstNameId>>lastNameId;
	}
};

typedef boost::shared_ptr<TaxCollectorName> TaxCollectorNamePtr;

#endif