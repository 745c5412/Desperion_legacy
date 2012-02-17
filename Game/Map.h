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

#ifndef __MAP__
#define __MAP__

#define ToCharacter(X) ((Character*)X)
#define ToMonsterGroup(X) ((MonsterGroup*)X)

struct Cell
{
	int16 id;
	uint8 losmov;
	int8 speed;
	uint8 mapChangeData;
};

struct MonsterGroup : DisplayableEntity
{
	void Init(int, int16, MonsterGrade*, std::vector<MonsterGrade*>&, Map*, int8);
	MonsterGrade* mainMonster;
	time_t spawnDate;
	std::vector<MonsterGrade*> monsters;
	virtual GameRolePlayActorInformations* ToActor();
	int16 GetAgeBonus() const;

	virtual bool IsMonsterGroup() const
	{ return true; }
};

class Map
{
public:
	Map() : m_currentActorId(0)
	{
	}

	~Map();
	void Init(Field*);
	DisplayableEntity* GetActor(int);
	void AddActor(DisplayableEntity*);
	void RemoveActor(int);
	void Send(const DofusMessage&, int guid = -1);
	PlayerItem* GetItem(int16);
	void AddItem(PlayerItem*, int16);
	void DeleteItem(int16);
	DisplayableEntity* GetEntityOnCell(int16);

	int GetId() const
	{ return m_id; }

	int16 GetPosX() const
	{ return m_posX; }

	int16 GetPosY() const
	{ return m_posY; }

	int16 GetSubAreaId() const
	{ return m_subareaId; }

	int GetCapabilities() const
	{ return m_capabilities; }

	std::list<DisplayableEntity*>& GetActors()
	{ return m_actors; }

	Cell GetCell(uint16) const;

	int GetTopMap() const
	{ return m_topMap; }

	int GetBottomMap() const
	{ return m_bottomMap; }

	int GetRightMap() const
	{ return m_rightMap; }

	int GetLeftMap() const
	{ return m_leftMap; }

	void SpawnMonsters(SubArea*, time_t);

	int GetNextActorId()
	{ return --m_currentActorId; }

	const std::unordered_map<int16, PlayerItem*>& GetItems() const
	{ return m_items; }

	bool SpawnSubAreaMonsters() const
	{ return m_spawnSubAreaMonsters; }
private:
	bool m_spawnSubAreaMonsters;
	int m_currentActorId;
	int m_id;
	int16 m_posX;
	int16 m_posY;
	int16 m_subareaId;
	int m_topMap;
	int m_bottomMap;
	int m_rightMap;
	int m_leftMap;
	int m_capabilities;
	std::list<DisplayableEntity*> m_actors;
	std::unordered_map<int16, PlayerItem*> m_items;
	std::vector<int> m_cells;
};

#endif