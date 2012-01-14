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

int GetLastConnectionDate(std::list<CharacterMinimals*>& chars)
{
	time_t last = 0;
	for(std::list<CharacterMinimals*>::iterator it2 = chars.begin(); it2 != chars.end(); ++it2)
		if((*it2)->lastConnectionDate > last)
			last = (*it2)->lastConnectionDate;
	return static_cast<int>((time(NULL) - last) / 3600);
}

std::istring GetOfflineCharacter(int guid)
{
	ResultPtr QR = Desperion::eDatabase.Query("SELECT pseudo FROM accounts WHERE guid=%u LIMIT 1;", guid);
	if(!QR)
		return "";
	Field* fields = QR->Fetch();
	return fields[0].GetString();
}

std::pair<int, std::istring> GetOfflineAccount(std::istring pseudo)
{
	ResultPtr QR = Desperion::eDatabase.Query("SELECT guid, pseudo FROM accounts WHERE LOWER(pseudo)='%s' LIMIT 1;",
		Desperion::ToLowerCase(Desperion::sDatabase.EscapeString(std::string(pseudo.c_str()))).c_str());
	if(!QR)
		return std::make_pair(0, "");
	Field* fields = QR->Fetch();
	return std::make_pair(fields[0].GetInt32(), std::istring(fields[1].GetString()));
}

void Session::HandleIgnoredGetListMessage(ByteBuffer& packet)
{
	IgnoredGetListMessage data;
	data.Deserialize(packet);

	std::vector<IgnoredInformationsPtr> list;
	for(boost::bimap<int, std::istring>::iterator it = m_ennemies.begin(); it != m_ennemies.end(); ++it)
	{
		Session* S = World::Instance().GetSession(it->get_left());
		if(S != NULL && S->GetCharacter() != NULL)
			list.push_back(IgnoredInformationsPtr(S->GetIgnoredInformations()));
		else
		{
			std::list<CharacterMinimals*> chars = World::Instance().GetCharactersByAccount(it->get_left());
			if(chars.empty())
				continue;
			list.push_back(IgnoredInformationsPtr(new IgnoredInformations(it->get_left(), S->GetData(FLAG_PSEUDO).stringValue)));
		}
	}
	Send(IgnoredListMessage(list));
}

void Session::HandleIgnoredDeleteRequestMessage(ByteBuffer& packet)
{
	IgnoredDeleteRequestMessage data;
	data.Deserialize(packet);

	boost::bimap<int, std::istring>& map = data.session ? m_ignored : m_ennemies;
	boost::bimap<int, std::istring>::right_iterator it = map.right.find(std::istring(data.name.c_str()));
	if(it == m_ignored.right.end())
	{
		Send(IgnoredDeleteResultMessage(false, data.session, data.name));
		return;
	}
	map.right.erase(it);
	Send(IgnoredDeleteResultMessage(true, data.session, data.name));
}

void Session::HandleIgnoredAddRequestMessage(ByteBuffer& packet)
{
	IgnoredAddRequestMessage data;
	data.Deserialize(packet);

	std::istring name(data.name.c_str());
	boost::bimap<int, std::istring>& map = data.session ? m_ignored : m_ennemies;
	if(m_subscriptionEnd - time(NULL) > 0 && map.size() >= 100)
	{
		Send(FriendAddFailureMessage(1));
		return;
	}
	else if(map.size() >= 50)
	{
		Send(FriendAddFailureMessage(1));
		return;
	}
	else if(Desperion::ToLowerCase(data.name) == Desperion::ToLowerCase(m_data[FLAG_PSEUDO].stringValue))
	{
		Send(FriendAddFailureMessage(3));
		return;
	}
	else if(map.right.find(name) != map.right.end())
	{
		Send(FriendAddFailureMessage(4));
		return;
	}

	Session* S = World::Instance().GetSession(data.name);
	if(S == NULL)
	{
		CharacterMinimals* ch = World::Instance().GetCharacterMinimals(data.name);
		if(ch != NULL && ch->onlineCharacter == NULL)
		{
			std::istring pseudo;
			if(!(pseudo = GetOfflineCharacter(ch->account)).empty())
			{
				if(map.right.find(pseudo) != map.right.end())
				{
					Send(FriendAddFailureMessage(4));
					return;
				}
				map.insert(boost::bimap<int, std::istring>::relation(ch->account, pseudo));
				Send(IgnoredAddedMessage(new IgnoredInformations(ch->account, std::string(pseudo.c_str())), data.session));
				return;
			}
		}
		else if(ch != NULL)
			S = ch->onlineCharacter->GetSession();
	}

	if(S != NULL)
	{
		map.insert(boost::bimap<int, std::istring>::relation(S->GetData(FLAG_GUID).intValue,
			std::istring(S->GetData(FLAG_PSEUDO).stringValue.c_str())));
		Send(IgnoredAddedMessage(S->GetIgnoredInformations(), data.session));
	}
	else
	{
		std::pair<int, std::istring> infos;
		if((infos = GetOfflineAccount(name)).first != 0)
		{
			if(map.right.find(infos.second) != map.right.end())
			{
				Send(FriendAddFailureMessage(4));
				return;
			}
			std::list<CharacterMinimals*> chars = World::Instance().GetCharactersByAccount(infos.first);
			if(chars.empty())
			{
				Send(IgnoredAddFailureMessage(1));
				return;
			}
			map.insert(boost::bimap<int, std::istring>::relation(infos.first, infos.second));
			Send(IgnoredAddedMessage(new IgnoredInformations(infos.first, std::string(infos.second.c_str())), data.session));
		}
		else
			Send(IgnoredAddFailureMessage(1));
	}
}

void Session::HandleFriendSetWarnOnConnectionMessage(ByteBuffer& packet)
{
	FriendSetWarnOnConnectionMessage data;
	data.Deserialize(packet);

	m_booleanValues[BOOL_FRIEND_WARN_ON_CONNECTION] = data.enable;
	Send(FriendWarnOnConnectionStateMessage(m_booleanValues[BOOL_FRIEND_WARN_ON_CONNECTION]));
}

void Session::HandleFriendSetWarnOnLevelGainMessage(ByteBuffer& packet)
{
	FriendSetWarnOnLevelGainMessage data;
	data.Deserialize(packet);

	m_booleanValues[BOOL_FRIEND_WARN_ON_LEVEL_GAIN] = data.enable;
	Send(FriendWarnOnLevelGainStateMessage(m_booleanValues[BOOL_FRIEND_WARN_ON_LEVEL_GAIN]));
}

void Session::HandleGuildMemberSetWarnOnConnectionMessage(ByteBuffer& packet)
{
	GuildMemberSetWarnOnConnectionMessage data;
	data.Deserialize(packet);

	m_booleanValues[BOOL_GUILD_MEMBER_WARN_ON_CONNECTION] = data.enable;
	Send(GuildMemberWarnOnConnectionStateMessage(m_booleanValues[BOOL_GUILD_MEMBER_WARN_ON_CONNECTION]));
}

void Session::HandleFriendAddRequestMessage(ByteBuffer& packet)
{
	FriendAddRequestMessage data;
	data.Deserialize(packet);

	std::istring name(data.name.c_str());
	if(m_subscriptionEnd - time(NULL) > 0 && m_friends.size() >= 100)
	{
		Send(FriendAddFailureMessage(1));
		return;
	}
	else if(m_friends.size() >= 50)
	{
		Send(FriendAddFailureMessage(1));
		return;
	}
	else if(Desperion::ToLowerCase(data.name) == Desperion::ToLowerCase(m_data[FLAG_PSEUDO].stringValue))
	{
		Send(FriendAddFailureMessage(3));
		return;
	}
	else if(m_friends.right.find(name) != m_friends.right.end()) // Todo: key comp
	{
		Send(FriendAddFailureMessage(4));
		return;
	}

	Session* S = World::Instance().GetSession(data.name);
	if(S == NULL)
	{
		CharacterMinimals* ch = World::Instance().GetCharacterMinimals(data.name);
		if(ch != NULL && ch->onlineCharacter == NULL)
		{
			std::istring pseudo;
			if(!(pseudo = GetOfflineCharacter(ch->account)).empty())
			{
				if(m_friends.right.find(pseudo) != m_friends.right.end()) // Todo: key comp
				{
					Send(FriendAddFailureMessage(4));
					return;
				}
				m_friends.insert(boost::bimap<int, std::istring>::relation(ch->account, pseudo));
				Send(FriendAddedMessage(new FriendInformations(ch->account, std::string(pseudo.c_str()), 0,
					GetLastConnectionDate(World::Instance().GetCharactersByAccount(ch->account)))));
				return;
			}
		}
		else if(ch != NULL)
			S = ch->onlineCharacter->GetSession();
	}

	if(S != NULL)
	{
		bool isFriend = S->IsFriendWith(m_data[FLAG_GUID].intValue);
		m_friends.insert(boost::bimap<int, std::istring>::relation(S->GetData(FLAG_GUID).intValue,
			std::istring(S->GetData(FLAG_PSEUDO).stringValue.c_str())));
		Send(FriendAddedMessage(S->GetFriendInformations(isFriend)));
	}
	else
	{
		std::pair<int, std::istring> infos;
		if((infos = GetOfflineAccount(name)).first != 0)
		{
			if(m_friends.right.find(infos.second) != m_friends.right.end()) // Todo: key comp
			{
				Send(FriendAddFailureMessage(4));
				return;
			}
			std::list<CharacterMinimals*> chars = World::Instance().GetCharactersByAccount(infos.first);
			if(chars.empty())
			{
				Send(FriendAddFailureMessage(2));
				return;
			}
			m_friends.insert(boost::bimap<int, std::istring>::relation(infos.first, infos.second));
			Send(FriendAddedMessage(new FriendInformations(infos.first, std::string(infos.second.c_str()), 0, GetLastConnectionDate(chars))));
		}
		else
			Send(FriendAddFailureMessage(2));
	}
}

void Session::HandleFriendDeleteRequestMessage(ByteBuffer& packet)
{
	FriendDeleteRequestMessage data;
	data.Deserialize(packet);

	boost::bimap<int, std::istring>::right_iterator it = m_friends.right.find(std::istring(data.name.c_str()));
	if(it == m_ignored.right.end())
	{
		Send(FriendDeleteResultMessage(false, data.name));
		return;
	}
	m_friends.right.erase(it);
	Send(FriendDeleteResultMessage(true, data.name));
}

void Session::HandleFriendsGetListMessage(ByteBuffer& packet)
{
	FriendsGetListMessage data;
	data.Deserialize(packet);

	std::vector<FriendInformationsPtr> list;
	for(boost::bimap<int, std::istring>::iterator it = m_friends.begin(); it != m_friends.end(); ++it)
	{
		Session* S = World::Instance().GetSession(it->get_left());
		if(S != NULL && S->GetCharacter() != NULL)
		{
			bool isFriend = S->IsFriendWith(m_data[FLAG_GUID].intValue);
			list.push_back(FriendInformationsPtr(S->GetFriendInformations(isFriend)));
		}
		else
		{
			std::list<CharacterMinimals*> chars = World::Instance().GetCharactersByAccount(it->get_left());
			if(chars.empty())
				continue;
			list.push_back(FriendInformationsPtr(new FriendInformations(it->get_left(), std::string(it->get_right().c_str()),
				0, GetLastConnectionDate(chars))));
		}
	}
	Send(FriendsListMessage(list));
}