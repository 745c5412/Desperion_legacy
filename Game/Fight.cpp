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

void Fight::GeneratePossiblePositions(std::set<int16>& list)
{
	while(list.size() != 8)
	{
		int16 index = 0;
		while(index == 0)
		{
			index = RandomUInt(0, 559);
			Cell c = m_map->GetCell(index);
			if(c.id == -1 || (c.losmov & 1) != 1)
				index = -1;
		}
		list.insert(index);
	}
}

void Fight::SendPossiblePositions(Session* S)
{
	std::vector<int16> list1, list2;
	for(std::set<int16>::iterator it = m_possiblePositions1.begin(); it != m_possiblePositions1.end(); ++it)
		list1.push_back(*it);
	for(std::set<int16>::iterator it = m_possiblePositions2.begin(); it != m_possiblePositions2.end(); ++it)
		list1.push_back(*it);
	S->Send(GameFightPlacementPossiblePositionsMessage(list1, list2, 0));
}

void Fight::Init(std::list<Fighter*>& team1, std::list<Fighter*>& team2, FightType fightType, Map* map)
{
	m_fightType = fightType;
	m_map = map;
	m_timer = ThreadPool::Instance().TimedSchedule(boost::bind(&Fight::StartFight, this),
		boost::posix_time::seconds(29));
	GeneratePossiblePositions(m_possiblePositions1);
	GeneratePossiblePositions(m_possiblePositions2);
	
	for(std::list<Fighter*>::iterator it = team1.begin(); it != team1.end(); ++it)
		AddFighter(*it, m_team1);
	for(std::list<Fighter*>::iterator it = team2.begin(); it != team2.end(); ++it)
		AddFighter(*it, m_team2);
	Send(GameFightUpdateTeamMessage(0, GetFightTeamInformations(m_team1, 0, 0)));
	Send(GameFightUpdateTeamMessage(0, GetFightTeamInformations(m_team2, 1, 1))); // todo: 0 = fightId
}

FightTeamInformations* Fight::GetFightTeamInformations(std::list<Fighter*>& team, int8 teamSide, int8 teamType)
{
	std::vector<FightTeamMemberInformationsPtr> teamMembers;
	for(std::list<Fighter*>::iterator it = team.begin(); it != team.end(); ++it)
		teamMembers.push_back(FightTeamMemberInformationsPtr((*it)->ToFightTeamMember()));
	return new FightTeamInformations(RandomUInt(1, 32767), (*team.begin())->GetGuid(), teamSide, teamType,
		teamMembers);
}

void Fight::Synchronize(bool prepa)
{
	std::vector<GameFightFighterInformationsPtr> list;
	for(std::list<Fighter*>::iterator it = m_team1.begin(); it != m_team1.begin(); ++it)
		list.push_back(GameFightFighterInformationsPtr((*it)->ToFightFighter(prepa)));
	for(std::list<Fighter*>::iterator it = m_team2.begin(); it != m_team2.begin(); ++it)
		list.push_back(GameFightFighterInformationsPtr((*it)->ToFightFighter(prepa)));
	Send(GameFightSynchronizeMessage(list));
}

void Fight::AddFighter(Fighter* fighter, std::list<Fighter*>& team)
{
	team.push_back(fighter);
	fighter->SetCell(GetRandomPossiblePosition(fighter->GetTeam()));
	if(fighter->IsPlayer())
	{
		PlayerFighter* pf = (PlayerFighter*)fighter;
		m_map->RemoveActor(pf->GetGuid());
		m_map->Send(GameContextRemoveElementMessage((pf->GetGuid())));
		pf->GetCharacter()->GetSession()->Send(GameContextDestroyMessage());
		//pf->GetCharacter()->GetSession()->Send(GameContextCreateMessage(FIGHT));
		pf->GetCharacter()->GetSession()->Send(GameFightStartingMessage(m_fightType));
		pf->GetCharacter()->GetSession()->Send(GameFightJoinMessage(false, true, false, false, 29, m_fightType));
		SendPossiblePositions(pf->GetCharacter()->GetSession());
	}
	Send(GameFightShowFighterMessage(fighter->ToFightFighter(true)));
}

void Fight::UpdateTimeLine()
{
	if(m_currentState == PREPHASE)
	{
		m_team1.sort(fightSort());
		m_team2.sort(fightSort());

		m_timeLine.clear();
		Team first = (*m_team1.begin())->GetInitiative() > (*m_team2.begin())->GetInitiative() ?
			TEAM1 : TEAM2;
		Team cur = first;
		std::list<Fighter*>::iterator it1, it2;
		for(it1 = m_team1.begin(), it2 = m_team2.begin(); (first == TEAM1 ? it1 : it2) !=
			(first == TEAM1 ? m_team1 : m_team2).end(); (cur == TEAM1 ? ++it1 : ++it2))
		{
			m_timeLine.push_back((cur == TEAM1 ? (*it1) : (*it2))->GetGuid());
			cur = (cur == TEAM1 ? TEAM2 : TEAM1);
		}
		for(std::list<Fighter*>::iterator it = (first == TEAM1 ? it2 : it1); it !=
			(first == TEAM1 ? m_team2 : m_team1).end(); ++it)
			m_timeLine.push_back((*it)->GetGuid());
	}
}

void Fight::Send(DofusMessage& message, Team team)
{
	struct send
	{
		send(DofusMessage& message, std::list<Fighter*>& list)
		{
			for(std::list<Fighter*>::iterator it = list.begin(); it != list.end(); ++it)
				if((*it)->IsPlayer())
					((PlayerFighter*)(*it))->GetCharacter()->GetSession()->Send(message);
		}
	};
	if(team == TEAM1 || team == UNK)
		send(message, m_team1);
	if(team == TEAM2 || team == UNK)
		send(message, m_team2);
}

Fighter* Fight::GetFighter(int id)
{
	for(std::list<Fighter*>::iterator it = m_team1.begin(); it != m_team1.end(); ++it)
		if((*it)->GetGuid() == id)
			return *it;
	for(std::list<Fighter*>::iterator it = m_team2.begin(); it != m_team2.end(); ++it)
		if((*it)->GetGuid() == id)
			return *it;
	return NULL;
}

void Fight::OnPlayerToggleReady(int fighterId)
{
	Fighter* fighter = GetFighter(fighterId);
	if(fighter == NULL)
		return;
	fighter->SetIsReady(!fighter->IsReady());
	Send(GameFightHumanReadyStateMessage(fighter->GetGuid(), fighter->IsReady()));
	for(std::list<Fighter*>::iterator it = m_team1.begin(); it != m_team1.end(); ++it)
		if(!(*it)->IsReady())
			return;
	for(std::list<Fighter*>::iterator it = m_team2.begin(); it != m_team2.end(); ++it)
		if(!(*it)->IsReady())
			return;
	m_timer->cancel();
	StartFight();
}

void Fight::NextTurn(bool nextFighter)
{
	if(nextFighter)
	{
		if(++m_currentFighterIterator == m_timeLine.end())
		{
			Send(GameFightNewRoundMessage(++m_round));
			m_currentFighterIterator = m_timeLine.begin();
		}
	}
	m_currentFighter = GetFighter(*m_currentFighterIterator);
	assert(m_currentFighter != NULL);
}

int16 Fight::GetRandomPossiblePosition(Team team)
{
	uint8 index = RandomUInt(0, 7);
	uint8 a = 0;
	std::set<int16>& list = team == TEAM1 ? m_possiblePositions1 : m_possiblePositions2;
	for(std::set<int16>::iterator it = list.begin(); it != list.end(); ++it)
	{
		if(a == index && GetFighter(*it) == NULL)
			return *it;
		++a;
	}
	return -1;
}

void Fight::SendDispositions()
{
	std::vector<IdentifiedEntityDispositionInformationsPtr> list;
	for(std::list<Fighter*>::iterator it = m_team1.begin(); it != m_team1.end(); ++it)
	{
		list.push_back(IdentifiedEntityDispositionInformationsPtr(
			(IdentifiedEntityDispositionInformations*)(*it)->GetEntityDispositionInformations(true)));
	}
	Send(GameEntitiesDispositionMessage(list));
}

Fighter* Fight::GetFighterOnCell(int16 cell)
{
	for(std::list<Fighter*>::iterator it = m_team1.begin(); it != m_team1.end(); ++it)
		if((*it)->GetCell() == cell)
			return *it;
	for(std::list<Fighter*>::iterator it = m_team2.begin(); it != m_team2.end(); ++it)
		if((*it)->GetCell() == cell)
			return *it;
	return NULL;
}

bool Fight::ExistsPossiblePosition(int16 cell, Team team)
{
	if(GetFighterOnCell(cell) != NULL)
		return false;
	if(team == TEAM1)
		return m_possiblePositions1.find(cell) != m_possiblePositions1.end();
	else
		return m_possiblePositions2.find(cell) != m_possiblePositions2.end();
}

void Fight::StartFight()
{
	UpdateTimeLine();
	m_currentState = FIGHTING;
	SendDispositions();
	Send(GameFightStartMessage());
	Synchronize(false);
	
	m_currentFighterIterator = m_timeLine.begin();
	Send(GameFightNewRoundMessage(++m_round));
	NextTurn(false);
}