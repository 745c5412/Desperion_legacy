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
	m.monsterId = infos[0];
	m.spawnProbability = infos[1];
	m.maxPerZone = infos[2];
	return m;
}

class Subarea
{
private:
	int16 m_id;
	int m_areaId;
	std::list<Map*> m_maps;
	std::vector<MonsterSpawnInformations> m_spawns;
public:
	Subarea()
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