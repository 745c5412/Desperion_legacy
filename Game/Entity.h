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

#ifndef __DISPLAYABLE_ENTITY__
#define __DISPLAYABLE_ENTITY__

class Map;

class DisplayableEntity
{
public:
	void Init(int, DEntityLook&, int16, Map*, int8);

	virtual EntityLook* GetLook() const
	{ return new EntityLook(m_look, std::vector<SubEntityPtr>()); }

	int16 GetCell() const
	{ return m_cell; }

	void SetCell(int16 cell)
	{ m_cell = cell; }

	Map* GetMap() const
	{ return m_map; }

	void SetMap(Map* map)
	{ m_map = map; }

	int GetGuid() const
	{ return m_guid; }

	int8 GetDirection() const
	{ return m_direction; }

	void SetDirection(int8 dir)
	{ m_direction = dir; }

	virtual GameRolePlayActorInformations* ToActor() const
	{
		return new GameRolePlayActorInformations(m_guid, GetLook(), GetEntityDispositionInformations());
	}

	virtual EntityDispositionInformations* GetEntityDispositionInformations() const
	{
		return new EntityDispositionInformations(m_cell, m_direction);
	}

	virtual bool IsCharacter() const
	{ return false; }

	virtual bool IsMonsterGroup() const
	{ return false; }
protected:
	int8 m_direction;
	int m_guid;
	DEntityLook m_look;
	int16 m_cell;
	Map* m_map;
};

class NamedEntity : public DisplayableEntity
{
public:
	void Init(std::string name);

	std::string GetName() const
	{ return m_name; }

	virtual GameRolePlayActorInformations* ToActor() const
	{
		return new GameRolePlayNamedActorInformations(m_guid, GetLook(), new EntityDispositionInformations(m_cell, m_direction),
			m_name);
	}
protected:
	std::string m_name;
};

enum Restriction
{
	cantBeAggressed,
	cantBeChallenged,
	cantTrade,
	cantBeAttackedByMutant,
	cantRun,
	forceSlowWalk,
	cantMinimize,
	cantMove,
	cantAggress,
	cantChallenge,
	cantExchange,
	cantAttack,
	cantChat,
	cantBeMerchant,
	cantUseObject,
	cantUseTaxCollector,
	cantUseInteractive,
	cantSpeakToNPC,
	cantChangeZone,
	cantAttackMonster,
	cantWalk8Directions,
	RESTRICTIONS_NUMBER,
};

class HumanEntity : public NamedEntity
{
public:
	void Init(int8, uint64, int16, std::string);

	int8 GetCurrentEmote() const
	{ return m_emoteId; }

	void SetCurrentEmote(int8 e)
	{ m_emoteId = e; }

	int64 GetEmoteStartTime() const
	{ return m_emoteStartTime; }

	void SetEmoteStartTime(int64 t)
	{ m_emoteStartTime = t; }

	bool GetRestriction(uint8 r) const
	{ return m_restrictions[r]; }

	void SetRestiction(uint8 r, bool v)
	{ m_restrictions[r] = v; }

	int16 GetTitle() const
	{ return m_title; }

	std::string GetTitleParams() const
	{ return m_titleParams; }

	const std::vector<EntityLookPtr>& GetFollowingCharacters() const
	{ return m_followingCharacters; }

	HumanInformations* GetHumanInfos() const
	{
		return new HumanInformations(m_followingCharacters, m_emoteId, m_emoteStartTime, 
			new ActorRestrictionsInformations(m_restrictions[cantBeAggressed], m_restrictions[cantBeChallenged], 
			m_restrictions[cantTrade], m_restrictions[cantBeAttackedByMutant], m_restrictions[cantRun], 
			m_restrictions[forceSlowWalk], m_restrictions[cantMinimize], m_restrictions[cantMove],
			m_restrictions[cantAggress], m_restrictions[cantChallenge], m_restrictions[cantExchange],
			m_restrictions[cantAttack], m_restrictions[cantChat], m_restrictions[cantBeMerchant], m_restrictions[cantUseObject],
			m_restrictions[cantUseTaxCollector], m_restrictions[cantUseInteractive], m_restrictions[cantSpeakToNPC],
			m_restrictions[cantChangeZone], m_restrictions[cantAttackMonster], m_restrictions[cantWalk8Directions]),
			m_title, "");
	}

	virtual GameRolePlayActorInformations* ToActor() const
	{ 
		return new GameRolePlayHumanoidInformations(m_guid, GetLook(), new EntityDispositionInformations(m_cell, m_direction),
			m_name, GetHumanInfos()); 
	}
protected:
	std::vector<EntityLookPtr> m_followingCharacters;
	int8 m_emoteId;
	int64 m_emoteStartTime;
	bool m_restrictions[RESTRICTIONS_NUMBER];
	int16 m_title;
	std::string m_titleParams;
};

#endif