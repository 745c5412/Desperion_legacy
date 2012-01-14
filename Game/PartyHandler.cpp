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

void Session::HandlePartyInvitationRequestMessage(ByteBuffer& packet)
{
	INIT_PARTY_LOCK
	PartyInvitationRequestMessage data;
	data.Deserialize(packet);
	
	std::string lower = Desperion::ToLowerCase(data.name);
	if(lower == Desperion::ToLowerCase(m_char->GetName())
		|| lower == m_data[FLAG_PSEUDO].stringValue)
		return;

	Session* S = SearchForSession(data.name);
	if(S == NULL)
	{
		Send(PartyCannotJoinErrorMessage(0, 1));
		return;
	}
	else if(m_party != NULL && m_party->m_players.size() + m_party->m_guests.size() >= 8)
	{
		Send(PartyCannotJoinErrorMessage(0, 3));
		return;
	}
	for(std::map<int, Session*>::iterator it = S->m_partyInvitations.begin(); it != S->m_partyInvitations.end(); ++it)
	{
		if(it->second->GetData(FLAG_GUID).intValue == m_data[FLAG_GUID].intValue)
		{
			Send(PartyCannotJoinErrorMessage(0, 6));
			return;
		}
	}
	
	if(m_party == NULL)
	{
		std::vector<PartyMemberInformationsPtr> members;
		members.push_back(PartyMemberInformationsPtr(m_char->GetPartyMemberInformations()));
		m_party = new Party;
		PARTY_LOCK(m_party)
		m_party->SetPartyId(static_cast<int>(RandomUInt()));
		m_party->SetLeader(this);
		Send(PartyJoinMessage(m_party->GetPartyId(), 0, m_char->GetGuid(), 8, members, std::vector<PartyGuestInformationsPtr>(), false));
	}
	if(!lock)
		PARTY_LOCK(m_party)
	S->m_partyInvitations[m_party->GetPartyId()] = this;
	m_party->Push(&Party::m_guests, S);
	m_party->SetGuestHost(S->GetCharacter()->GetGuid(), m_char->GetGuid());
	m_party->Send(PartyNewGuestMessage(m_party->GetPartyId(), S->GetCharacter()->GetPartyGuestInformations(m_data[FLAG_GUID].intValue)));
	S->Send(PartyInvitationMessage(m_party->GetPartyId(), 0, 8, m_char->GetGuid(), m_char->GetName(), S->GetCharacter()->GetGuid()));
}

void Session::HandlePartyRefuseInvitationMessage(ByteBuffer& packet)
{
	INIT_PARTY_LOCK
	PartyRefuseInvitationMessage data;
	data.Deserialize(packet);
	
	std::map<int, Session*>::iterator it = m_partyInvitations.find(data.partyId);
	if(it == m_partyInvitations.end())
		return;
	Session* S = it->second;
	m_partyInvitations.erase(it);

	if(S->m_party == NULL)
		return;
	PARTY_LOCK(S->m_party)
	Send(PartyInvitationCancelledForGuestMessage(S->m_party->GetPartyId(), m_char->GetGuid()));
	S->m_party->Delete(&Party::m_guests, m_char->GetGuid());
	S->m_party->IntegrityCheck(lock);
}

void Session::HandlePartyCancelInvitationMessage(ByteBuffer& packet)
{
	INIT_PARTY_LOCK
	PartyCancelInvitationMessage data;
	data.Deserialize(packet);

	if(m_party == NULL)
		return;
		
	PARTY_LOCK(m_party)
	std::list<Session*>::iterator it = m_party->Get(&Party::m_guests, data.guestId);
	if(it == m_party->End(&Party::m_guests))
		return;
	(*it)->Send(PartyInvitationCancelledForGuestMessage(m_party->GetPartyId(), m_char->GetGuid()));
	(*it)->m_partyInvitations.erase((*it)->m_partyInvitations.find(data.partyId));
	m_party->Delete(&Party::m_guests, (*it)->GetCharacter()->GetGuid(), true);
	m_party->Send(PartyCancelInvitationNotificationMessage(m_party->GetPartyId(), m_char->GetGuid(), data.guestId));
	m_party->IntegrityCheck(lock);
}

void Session::HandlePartyAcceptInvitationMessage(ByteBuffer& packet)
{
	PartyAcceptInvitationMessage data;
	data.Deserialize(packet);

	std::map<int, Session*>::iterator it = m_partyInvitations.find(data.partyId);
	if(it == m_partyInvitations.end())
		return;
	Session* S = it->second;
	m_partyInvitations.erase(it);

	if(m_party != NULL)
	{
		INIT_PARTY_LOCK
		PARTY_LOCK(m_party)
		m_party->Delete(&Party::m_players, m_char->GetGuid());
		Send(PartyLeaveMessage(m_party->GetPartyId()));
		m_party->IntegrityCheck(lock);
		m_party = NULL;
	}
	m_party = S->m_party;
	INIT_PARTY_LOCK
	PARTY_LOCK(m_party)
	m_party->Push(&Party::m_players, this);
	m_party->Delete(&Party::m_guests, m_char->GetGuid(), true);
	std::vector<PartyMemberInformationsPtr> members;
	std::vector<PartyGuestInformationsPtr> guests;
	m_party->FillMembers(members), m_party->FillGuests(guests);
	Send(PartyJoinMessage(m_party->GetPartyId(), 0, m_party->GetLeader()->GetCharacter()->GetGuid(), 8, members, guests, false));
	m_party->Send(PartyNewMemberMessage(m_party->GetPartyId(), m_char->GetPartyMemberInformations()));
}

void Session::HandlePartyKickRequestMessage(ByteBuffer& packet)
{
	INIT_PARTY_LOCK
	PartyKickRequestMessage data;
	data.Deserialize(packet);

	if(m_party == NULL)
		return;

	PARTY_LOCK(m_party)
	std::list<Session*>::iterator it = m_party->Get(&Party::m_players, data.playerId);
	if(it == m_party->End(&Party::m_players))
		return;
	(*it)->Send(PartyKickedByMessage(m_party->GetPartyId(), m_char->GetGuid()));
	(*it)->m_party = NULL;
	m_party->Delete(&Party::m_players, (*it)->GetCharacter()->GetGuid());
	m_party->IntegrityCheck(lock);
}

void Session::HandlePartyInvitationDetailsRequestMessage(ByteBuffer& packet)
{
	INIT_PARTY_LOCK
	PartyInvitationDetailsRequestMessage data;
	data.Deserialize(packet);

	std::map<int, Session*>::iterator it = m_partyInvitations.find(data.partyId);
	if(it == m_partyInvitations.end())
		return;
		
	Session* S = it->second;
	if(S->m_party == NULL)
		return; // ne devrait pas arriver grace aux locks
	std::vector<PartyInvitationMemberInformationsPtr> members;
	PARTY_LOCK(S->m_party)
	S->m_party->FillInvitationMembers(members);
	Send(PartyInvitationDetailsMessage(S->m_party->GetPartyId(), 0, it->first, S->GetCharacter()->GetName(),
		S->m_party->GetLeader()->GetCharacter()->GetGuid(), members));
}

void Session::HandlePartyLeaveRequestMessage(ByteBuffer& packet)
{
	INIT_PARTY_LOCK
	PartyLeaveRequestMessage data;
	data.Deserialize(packet);

	if(m_party == NULL)
		return;
		
	PARTY_LOCK(m_party)
	m_party->Delete(&Party::m_players, m_char->GetGuid());
	Send(PartyLeaveMessage(m_party->GetPartyId()));
	m_party->IntegrityCheck(lock);
	m_party = NULL;
}

void Session::HandlePartyAbdicateThroneMessage(ByteBuffer& packet)
{
	INIT_PARTY_LOCK
	PartyAbdicateThroneMessage data;
	data.Deserialize(packet);

	if(m_party == NULL || data.playerId == m_char->GetGuid())
		return;
	PARTY_LOCK(m_party)
	if(m_party->GetLeader()->GetData(FLAG_GUID).intValue != m_data[FLAG_GUID].intValue)
		return;
	std::list<Session*>::iterator it = m_party->Get(&Party::m_players, data.playerId);
	if(it == m_party->End(&Party::m_players))
		return;
	m_party->SetLeader(*it);
	m_party->Erase(&Party::m_players, it);
	m_party->Push(&Party::m_players, this);
	m_party->Send(PartyLeaderUpdateMessage(m_party->GetPartyId(), m_party->GetLeader()->GetCharacter()->GetGuid()));
}