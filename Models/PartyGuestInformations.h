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

#ifndef __PARTY_GUEST_INFORMATIONS__
#define __PARTY_GUEST_INFORMATIONS__

class PartyGuestInformations : public DofusModel
{
public:
	int guestId;
	int hostId;
	std::string name;
	EntityLookPtr guestLook;

	uint16 GetProtocol() const
	{ return PARTY_GUEST_INFORMATIONS; }

	PartyGuestInformations()
	{
	}

	PartyGuestInformations(int guestId, int hostId, std::string name, EntityLook* guestLook) : guestId(guestId), hostId(hostId), name(name), guestLook(guestLook)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<guestId<<hostId<<name;
		guestLook->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>guestId>>hostId>>name;
		guestLook.reset(new EntityLook);
		guestLook->Deserialize(data);
	}
};

typedef boost::shared_ptr<PartyGuestInformations> PartyGuestInformationsPtr;

#endif