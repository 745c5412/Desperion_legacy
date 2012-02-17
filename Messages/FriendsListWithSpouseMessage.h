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

#ifndef __FRIENDS_LIST_WITH_SPOUSE_MESSAGE__
#define __FRIENDS_LIST_WITH_SPOUSE_MESSAGE__

class FriendsListWithSpouseMessage : public FriendsListMessage
{
public:
	FriendSpouseInformationsPtr spouse;

	uint16 GetOpcode() const
	{ return SMSG_FRIENDS_LIST_WITH_SPOUSE; }

	FriendsListWithSpouseMessage()
	{
	}

	FriendsListWithSpouseMessage(std::vector<FriendInformationsPtr>& friendsList, FriendSpouseInformations* spouse) : FriendsListMessage(friendsList), spouse(spouse)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		FriendsListMessage::Serialize(data);
		data<<spouse->GetProtocol();
		spouse->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		FriendsListMessage::Deserialize(data);
		uint16 protocol;
		data>>protocol;
		spouse.reset(Desperion::ProtocolTypeManager::GetFriendSpouseInformations(protocol));
		spouse->Deserialize(data);
	}
};

#endif