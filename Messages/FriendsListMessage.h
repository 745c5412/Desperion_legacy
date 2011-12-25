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

#ifndef __FRIENDS_LIST_MESSAGE__
#define __FRIENDS_LIST_MESSAGE__

class FriendsListMessage : public DofusMessage
{
public:
	std::vector<FriendInformationsPtr> friendsList;

	uint16 GetOpcode() const
	{ return SMSG_FRIENDS_LIST; }

	FriendsListMessage()
	{
	}

	FriendsListMessage(std::vector<FriendInformationsPtr>& friendsList) : friendsList(friendsList)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		uint16 size = friendsList.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
		{
			data<<friendsList[a]->GetProtocol();
			friendsList[a]->Serialize(data);
		}
	}

	void Deserialize(ByteBuffer& data)
	{
		friendsList.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			uint16 protocol;
			data>>protocol;
			FriendInformationsPtr model(Desperion::ProtocolTypeManager::GetFriendInformations(protocol));
			model->Deserialize(data);
			friendsList.push_back(model);
		}
	}
};

#endif