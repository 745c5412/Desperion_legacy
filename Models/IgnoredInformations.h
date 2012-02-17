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

#ifndef __IGNORED_INFORMATIONS__
#define __IGNORED_INFORMATIONS__

class IgnoredInformations : public AbstractContactInformations
{
public:

	uint16 GetProtocol() const
	{ return IGNORED_INFORMATIONS; }

	IgnoredInformations()
	{
	}
	
	IgnoredInformations(int accountId, std::string accountName) : AbstractContactInformations(accountId, accountName)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		AbstractContactInformations::Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		AbstractContactInformations::Deserialize(data);
	}
};

typedef boost::shared_ptr<IgnoredInformations> IgnoredInformationsPtr;

#endif