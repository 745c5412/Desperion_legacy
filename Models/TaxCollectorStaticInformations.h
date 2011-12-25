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

#ifndef __TAX_COLLECTOR_STATIC_INFORMATIONS__
#define __TAX_COLLECTOR_STATIC_INFORMATIONS__

class TaxCollectorStaticInformations : public DofusModel
{
public:
	int16 firstNameId;
	int16 lastNameId;
	GuildInformationsPtr guildIdentity;

	uint16 GetProtocol() const
	{ return TAX_COLLECTOR_STATIC_INFORMATIONS; }

	TaxCollectorStaticInformations()
	{
	}

	TaxCollectorStaticInformations(int16 firstNameId, int16 lastNameId, GuildInformations* guildIdentity) : firstNameId(firstNameId), lastNameId(lastNameId), guildIdentity(guildIdentity)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<firstNameId<<lastNameId;
		guildIdentity->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>firstNameId>>lastNameId;
		guildIdentity.reset(new GuildInformations);
		guildIdentity->Deserialize(data);
	}
};

typedef boost::shared_ptr<TaxCollectorStaticInformations> TaxCollectorStaticInformationsPtr;

#endif