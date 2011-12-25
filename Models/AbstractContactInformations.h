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

#ifndef __ABSTRACT_CONTACT_INFORMATIONS__
#define __ABSTRACT_CONTACT_INFORMATIONS__

class AbstractContactInformations : public DofusModel
{
public:
	int accountId;
	std::string accountName;

	uint16 GetProtocol() const
	{ return ABSTRACT_CONTACT_INFORMATIONS; }

	AbstractContactInformations()
	{
	}

	AbstractContactInformations(int accountId, std::string accountName) : accountId(accountId), accountName(accountName)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<accountId<<accountName;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>accountId>>accountName;
	}
};

typedef boost::shared_ptr<AbstractContactInformations> AbstractContactInformationsPtr;

#endif