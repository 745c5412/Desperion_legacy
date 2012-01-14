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

void Party::IntegrityCheck(boost::shared_ptr<boost::mutex::scoped_lock> lock)
{
	if(m_leader == NULL || (m_players.empty() && m_guests.empty()))
	{
		if(m_leader != NULL)
		{
			m_leader->Send(PartyDeletedMessage(m_partyId));
			m_leader->SetParty(NULL);
		}
		else if(!m_guests.empty())
		{
			for(std::list<Session*>::iterator it = m_guests.begin(); it != m_guests.end(); ++it)
			{
				(*it)->ErasePartyInvitation(m_partyId);
				(*it)->Send(PartyInvitationCancelledForGuestMessage(m_partyId,
					m_guestHosts[(*it)->GetCharacter()->GetGuid()])); // en theorie: uniquement des guests du leader
			}
		}
		lock->unlock();
		delete this;
	}
}
	
void Party::FillMembers(std::vector<PartyMemberInformationsPtr>& members)
{
	for(std::list<Session*>::iterator it = m_players.begin(); it != m_players.end(); ++it)
		members.push_back(PartyMemberInformationsPtr((*it)->GetCharacter()->GetPartyMemberInformations()));
	members.push_back(PartyMemberInformationsPtr(m_leader->GetCharacter()->GetPartyMemberInformations()));
}

void Party::FillInvitationMembers(std::vector<PartyInvitationMemberInformationsPtr>& members)
{
	for(std::list<Session*>::iterator it = m_players.begin(); it != m_players.end(); ++it)
		members.push_back(PartyInvitationMemberInformationsPtr((*it)->GetCharacter()->GetPartyInvitationMemberInformations()));
	members.push_back(PartyInvitationMemberInformationsPtr(m_leader->GetCharacter()->GetPartyInvitationMemberInformations()));
}

void Party::FillGuests(std::vector<PartyGuestInformationsPtr>& members)
{
	for(std::list<Session*>::iterator it = m_guests.begin(); it != m_guests.end(); ++it)
	{
		members.push_back(PartyGuestInformationsPtr((*it)->GetCharacter()->GetPartyGuestInformations(
			m_guestHosts[(*it)->GetCharacter()->GetGuid()])));
	}
}

std::list<Session*>::iterator Party::Get(std::list<Session*> Party::*list, int guid)
{
	for(std::list<Session*>::iterator it = (this->*list).begin(); it != (this->*list).end(); ++it)
		if((*it)->GetCharacter()->GetGuid() == guid)
			return it;
	return (this->*list).end();
}

void Party::Delete(std::list<Session*> Party::*list, int guid, bool isGuestCancel)
{
	if(guid == m_leader->GetCharacter()->GetGuid())
	{
		if(m_players.empty())
		{
			m_leader = NULL;
			return;
		}
		m_leader = *(m_players.begin());
		m_players.erase(m_players.begin());
		Send(PartyLeaderUpdateMessage(m_partyId, m_leader->GetCharacter()->GetGuid()));
	}
	else
	{
		for(std::list<Session*>::iterator it = (this->*list).begin(); it != (this->*list).end(); ++it)
		{
			if((*it)->GetCharacter()->GetGuid() == guid)
			{
				(this->*list).erase(it);
				break;
			}
		}
	}
	if(list == &Party::m_players)
	{
		std::list<Session*>::iterator it = m_guests.begin();
		while(it != m_guests.end())
		{
			if(m_guestHosts[(*it)->GetCharacter()->GetGuid()] != guid)
			{
				(*it)->ErasePartyInvitation(m_partyId);
				(*it)->Send(PartyInvitationCancelledForGuestMessage(m_partyId, guid));
				Send(PartyCancelInvitationNotificationMessage(m_partyId, guid, (*it)->GetCharacter()->GetGuid()));
				it = m_guests.erase(it);
			}
			else
				++it;
		}
		Send(PartyMemberRemoveMessage(m_partyId, guid));
	}
	else
	{
		m_guestHosts.erase(m_guestHosts.find(guid));
		if(!isGuestCancel)
			Send(PartyRefuseInvitationNotificationMessage(m_partyId, guid));
	}
}

void Party::Send(DofusMessage& message, int self)
{
	for(std::list<Session*>::iterator it = m_players.begin(); it != m_players.end(); ++it)
	{
		if((*it)->GetData(FLAG_GUID).intValue == self)
			continue;
		(*it)->Send(message);
	}
	if(m_leader->GetData(FLAG_GUID).intValue != self)
		m_leader->Send(message);
}