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

#include "StdAfx.h"

void Session::HandleFriendsGetListMessage(ByteBuffer& data)
{
	std::vector<FriendInformationsPtr> list;
	for(boost::bimap<int, std::string>::iterator it = m_friends.begin(); it != m_friends.end(); ++it)
	{
		Session* S = World::Instance().GetSession(it->get_left());
		if(S != NULL && S->GetCharacter() != NULL)
		{
			list.push_back(FriendInformationsPtr(new FriendOnlineInformations(S->GetData(FLAG_GUID).intValue,
				S->GetData(FLAG_PSEUDO).stringValue, S->GetCharacter()->GetContextType(), 0, S->GetCharacter()->GetName(),
				S->GetCharacter()->GetLevel(), S->GetCharacter()->GetStats().GetAlignmentSide(), S->GetCharacter()->GetBreed(),
				S->GetCharacter()->GetSex(), new BasicGuildInformations(0, ""), S->GetCharacter()->GetSmileyId())));
		}
		else
		{
			std::list<CharacterMinimals*> chars = World::Instance().GetCharactersByAccount(it->get_left());
			if(chars.empty())
				continue;
			time_t last = 0;
			for(std::list<CharacterMinimals*>::iterator it2 = chars.begin(); it2 != chars.end(); ++it2)
				if((*it2)->lastConnectionDate > last)
					last = (*it2)->lastConnectionDate;
			list.push_back(FriendInformationsPtr(new FriendInformations(it->get_left(), it->get_right(), 0, static_cast<int>(last))));
		}
	}
}