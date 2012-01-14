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

#ifndef __SUBAREA__
#define __SUBAREA__

struct MonsterSpawnInformations
{
	int monsterId;
	double spawnProbability;
	int maxPerZone;
};

inline MonsterSpawnInformations S(std::string& str)
{
	std::vector<double> infos;
	Desperion::FastSplit<','>(infos, str, Desperion::SplitDouble, true);
	MonsterSpawnInformations m;
	m.monsterId = static_cast<int>(infos[0]);
	m.spawnProbability = infos[1];
	m.maxPerZone = static_cast<int>(infos[2]);
	return m;
}

class SubArea
{
private:
	int16 m_id;
	int m_areaId;
	std::list<Map*> m_maps;
	std::vector<MonsterSpawnInformations> m_spawns;
	std::map<int, uint16> m_monsterCounts;
	std::map<int, time_t> m_monsterSpawnDates;
public:
	SubArea()
	{
	}

	time_t GetMonsterSpawnDate(int id)
	{
		std::map<int, time_t>::iterator it = m_monsterSpawnDates.find(id);
		if(it == m_monsterSpawnDates.end())
		{
			m_monsterSpawnDates[id] = 0;
			return 0;
		}
		return it->second;
	}

	void SetMonsterSpawnDate(int id, time_t date)
	{ m_monsterSpawnDates[id] = date; }
	
	uint16 GetMonsterCount(int id)
	{
		std::map<int, uint16>::iterator it = m_monsterCounts.find(id);
		if(it == m_monsterCounts.end())
		{
			m_monsterCounts[id] = 0;
			return 0;
		}
		return it->second;
	}

	void IncMonsterCount(int id)
	{
		std::map<int, uint16>::iterator it = m_monsterCounts.find(id);
		if(it == m_monsterCounts.end())
			m_monsterCounts[id] = 1;
		else
			++m_monsterCounts[id];
	}

	std::vector<MonsterSpawnInformations>& GetPossibleSpawns()
	{ return m_spawns; }

	std::list<Map*>& GetMaps()
	{ return m_maps; }

	void Init(Field*);
	void Send(DofusMessage&);

	int16 GetId() const
	{ return m_id; }

	int GetAreaId() const
	{ return m_areaId; }

	void AddMap(Map* map)
	{ m_maps.push_back(map); }
};

#endif