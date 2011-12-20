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
public:
	SubArea()
	{
	}

	void Init(Field*);

	int16 GetId() const
	{ return m_id; }

	int GetAreaId() const
	{ return m_areaId; }

	void AddMap(Map* map)
	{ m_maps.push_back(map); }
};

#endif