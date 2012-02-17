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

#ifndef __FIGHT__
#define __FIGHT__

enum Team
{
	UNK = 0,
	TEAM1 = 1,
	TEAM2 = 2,
};

enum ComputerType
{
	NOT_COMPUTER,
	IS_MONSTER,
	IS_DOUBLE,
	IS_TAX_COLLECTOR,
	IS_INVOCATION,
};

class Fighter
{
protected:
	std::tr1::unordered_map<int, int> m_coolDowns;
	std::tr1::unordered_map<int, int> m_spellCounts;
	bool m_isReady;
	bool m_isDead;
	Team m_team;
	ComputerType m_computerType;
	int m_baseMaxLife;
	int m_carryingCharacterId;
	
public:
	Fighter(Team team, ComputerType computerType, int baseMaxLife) : m_team(team), m_computerType(computerType),
		m_isDead(false), m_baseMaxLife(baseMaxLife), m_carryingCharacterId(0)
	{
	}

	bool IsDead() const
	{ return m_isDead; }

	void SetIsDead(bool d)
	{ m_isDead = d; }

	Team GetTeam() const
	{ return m_team; }

	bool IsReady() const
	{ return m_isReady; }
	
	void SetIsReady(bool r)
	{ m_isReady = r; }

	void SetSpellCount(int id, int count)
	{ m_coolDowns[id] = count; }

	void SetCoolDown(int id, int coolDown)
	{ m_coolDowns[id] = coolDown; }
	
	int GetCoolDown(int id)
	{
		std::tr1::unordered_map<int, int>::iterator it = m_coolDowns.find(id);
		if(it == m_coolDowns.end())
			return -1;
		return it->second;
	}
	
	int GetSpellCount(int id)
	{
		std::tr1::unordered_map<int, int>::iterator it = m_spellCounts.find(id);
		if(it == m_spellCounts.end())
			return 0;
		return it->second;
	}
	
	virtual bool IsPlayer() const
	{ return false; }
	
	virtual bool IsMonster() const
	{ return false; }
	
	virtual int GetInitiative() = 0; // const?
	virtual int16 GetCell() const = 0;
	virtual void SetCell(int16) = 0;
	virtual int GetGuid() const = 0;
	virtual GameFightFighterInformations* ToFightFighter(bool) = 0;
	virtual EntityDispositionInformations* GetEntityDispositionInformations(bool) = 0;
	virtual FightTeamMemberInformations* ToFightTeamMember() = 0;
};

class PlayerFighter : public Fighter
{
private:
	Character* m_character;
	
public:
	PlayerFighter(Team team, Character* ch, int baseMaxLife) : Fighter(team, NOT_COMPUTER, baseMaxLife),
		m_character(ch)
	{
	}
	
	Character* GetCharacter()
	{ return m_character; }
	
	bool IsPlayer() const
	{ return true; }
	
	int GetInitiative()
	{ return m_character->GetStats().initiative.Total(); }
	
	int GetGuid() const
	{ return m_character->GetGuid(); }

	EntityDispositionInformations* GetEntityDispositionInformations(bool prepa)
	{
		if(prepa)
		{
			return new FightEntityDispositionInformations(m_character->GetCell(), m_character->GetDirection(),
				m_carryingCharacterId);
		}
		else
		{
			return new IdentifiedEntityDispositionInformations(m_character->GetCell(),
				m_character->GetDirection(), m_character->GetGuid());
		}
	}
	
	FightTeamMemberInformations* ToFightTeamMember()
	{
		return new FightTeamMemberCharacterInformations(m_character->GetGuid(), m_character->GetName(), m_character->GetLevel());
	}

	int16 GetCell() const
	{ return m_character->GetCell(); }

	void SetCell(int16 c)
	{ m_character->SetCell(c); }

	GameFightFighterInformations* ToFightFighter(bool prepa)
	{
		GameFightMinimalStats* stats = new GameFightMinimalStats(
			m_character->GetCurrentLife(), m_character->GetMaxLife(), m_baseMaxLife,
			m_character->GetStats().permanentDamagePercent.Total(), 0, m_character->GetStats().GetCurrentAp(),
			m_character->GetStats().actionPoints.Total(), m_character->GetStats().GetCurrentMp(),
			m_character->GetStats().movementPoints.Total(), 0, false, m_character->GetStats().neutralElementResistPercent.Total(),
			m_character->GetStats().earthElementResistPercent.Total(), m_character->GetStats().waterElementResistPercent.Total(),
			m_character->GetStats().airElementResistPercent.Total(), m_character->GetStats().fireElementResistPercent.Total(),
			m_character->GetStats().dodgePALostProbability.Total(), m_character->GetStats().dodgePMLostProbability.Total(),
			m_character->GetStats().tackleBlock.Total(), m_character->GetStats().tackleEvade.Total(), 0);
		GameFightMinimalStatsPreparation* stats2 = (GameFightMinimalStatsPreparation*)stats;
		stats2->initiative = GetInitiative();

		return new GameFightCharacterInformations(m_character->GetGuid(), m_character->GetLook(),
			GetEntityDispositionInformations(prepa), m_team, !m_isDead, prepa ? stats2 : stats,
			m_character->GetName(), m_character->GetLevel(), m_character->GetActorAlignmentInformations());
	}
};

class MonsterFighter : public Fighter
{
private:
	MonsterGrade* m_monster;
	int m_lostAp;
	int m_lostMp;
	int m_fightGuid;
	int m_damages;
	int m_cell;
	int m_direction;
	// todo: stats completes en vue des buffs
	
public:
	MonsterFighter(Team team, MonsterGrade* mg) : Fighter(team, IS_MONSTER, mg->lifePoints),
		m_monster(mg), m_lostAp(0), m_lostMp(0), m_fightGuid(-static_cast<int>(RandomUInt(1, 32767))),
		m_damages(0), m_direction(1)
	{
		SetIsReady(true);
	}

	int GetMaxLife()
	{ return m_monster->lifePoints; } // todo: buff

	int GetCurrentLife()
	{
		int life = GetMaxLife() - m_damages;
		if(life < 0)
			life = 0;
		return life;
	}

	int16 GetCell() const
	{ return m_cell; }

	void SetCell(int16 c)
	{ m_cell = c; }

	EntityDispositionInformations* GetEntityDispositionInformations(bool prepa)
	{
		if(prepa)
			return new FightEntityDispositionInformations(m_cell, m_direction, m_carryingCharacterId);
		else
			return new IdentifiedEntityDispositionInformations(m_cell, m_direction, m_fightGuid);
	}

	GameFightFighterInformations* ToFightFighter(bool prepa)
	{
		GameFightMinimalStats* stats = new GameFightMinimalStatsPreparation(
			GetCurrentLife(), GetMaxLife(), m_monster->lifePoints,
			0, 0, m_monster->actionPoints - m_lostAp, m_monster->actionPoints, m_monster->movementPoints - m_lostMp,
			m_monster->movementPoints, 0, false, m_monster->neutralResistance, m_monster->earthResistance,
			m_monster->waterResistance, m_monster->airResistance, m_monster->fireResistance,
			m_monster->paDodge, m_monster->pmDodge, 0, 0, 0, GetInitiative()); // todo: buffs aussi :)

		return new GameFightMonsterInformations(m_fightGuid, new EntityLook(World::Instance().GetMonster(m_monster->monsterId)->GetLook(),
			std::vector<SubEntityPtr>()), GetEntityDispositionInformations(prepa), m_team, !m_isDead, stats, m_monster->monsterId,
			m_monster->grade);
	}
	
	FightTeamMemberInformations* ToFightTeamMember()
	{
		return new FightTeamMemberMonsterInformations(m_fightGuid, m_monster->monsterId, m_monster->grade);
	}
	
	MonsterGrade* GetMonster()
	{ return m_monster; }
	
	bool IsMonster() const
	{ return true; }
	
	int GetInitiative()
	{ return 0; } // todo
	
	int GetGuid() const
	{ return m_fightGuid; }
};

enum FightState
{
	PREPHASE,
	FIGHTING,
};

enum FightType
{
	PVM,
	PVP,
	PVT,
	CHALLENGE,
};

struct fightSort
{
	bool operator()(Fighter* f1, Fighter* f2)
	{ return f1->GetInitiative() < f2->GetInitiative(); }
};

class Fight
{
private:
	std::list<Fighter*> m_team1, m_team2;
	int m_round;
	Fighter* m_currentFighter;
	std::list<int>::iterator m_currentFighterIterator;
	std::list<int> m_timeLine;
	std::set<int16> m_possiblePositions1, m_possiblePositions2;
	time_t m_startTime;
	FightState m_currentState;
	FightType m_fightType;
	boost::shared_ptr<boost::asio::deadline_timer> m_timer;
	Map* m_map;
	
public:
	Fight() : m_startTime(time(NULL)), m_currentState(PREPHASE), m_round(0)
	{
	}
	
	FightTeamInformations* GetFightTeamInformations(std::list<Fighter*>&, int8, int8);
	void SendDispositions();
	int16 GetRandomPossiblePosition(Team);
	bool ExistsPossiblePosition(int16, Team);
	void Synchronize(bool);
	void GeneratePossiblePositions(std::set<int16>&);
	void SendPossiblePositions(Session*);
	void AddFighter(Fighter*, std::list<Fighter*>&);
	void Init(std::list<Fighter*>&, std::list<Fighter*>&, FightType, Map*);
	void UpdateTimeLine();
	void StartFight();
	void NextTurn(bool);
	void Send(DofusMessage&, Team team = UNK);
	void OnPlayerToggleReady(int);
	Fighter* GetFighter(int);
	Fighter* GetFighterOnCell(int16);
};

#endif