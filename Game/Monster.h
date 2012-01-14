#ifndef __MONSTER__
#define __MONSTER__

class Monster;

struct MonsterGrade
{
	int lifePoints;
	int monsterId;
	int8 grade;
	int pmDodge;
	int level;
	int actionPoints;
	int wisdom;
	int movementPoints;
	int paDodge;
	int earthResistance;
	int neutralResistance;
	int airResistance;
	int fireResistance;
	int waterResistance;
	int gradeXp;
};

struct MonsterStats
{
	MonsterStats() : strength(0), intelligence(0),
		chance(0), agility(0)
	{
	}

	int strength;
	int intelligence;
	int chance;
	int agility;
};

inline MonsterStats* MS(std::string& str)
{
	std::vector<int> table;
	Desperion::FastSplit<','>(table, str, Desperion::SplitInt);
	MonsterStats* ms = new MonsterStats;
	ms->strength = table[0];
	ms->intelligence = table[1];
	ms->chance = table[2];
	ms->agility = table[3];
	return ms;
}

inline MonsterGrade* M(std::string& str)
{
	std::vector<int> table;
	Desperion::FastSplit<','>(table, str, Desperion::SplitInt);
	MonsterGrade* m = new MonsterGrade;
	m->lifePoints = table[0];
	m->monsterId = table[1];
	m->grade = table[2];
	m->pmDodge = table[3];
	m->level = table[4];
	m->actionPoints = table[5];
	m->wisdom = table[6];
	m->movementPoints = table[7];
	m->paDodge = table[8];
	m->earthResistance = table[9];
	m->neutralResistance = table[10];
	m->airResistance = table[11];
	m->fireResistance = table[12];
	m->waterResistance = table[13];
	m->gradeXp = table[14];
	return m;
}

class Monster
{
private:
	int m_id;
	int m_gfxId;
	int m_race;
	std::vector<MonsterGrade*> m_grades;
	std::vector<MonsterStats*> m_gradesStats;
	bool m_canPlay;
	bool m_canTackle;
	bool m_isBoss;
	DEntityLook m_look;
	time_t m_minRespawnTime;
public:
	Monster()
	{
	}

	~Monster();

	void Init(Field* fields);

	time_t GetMinRespawnTime() const
	{ return m_minRespawnTime; }

	int GetId() const
	{ return m_id; }

	int GetGfxId() const
	{ return m_gfxId; }

	int GetRace() const
	{ return m_race; }

	size_t GetGradesSize() const
	{ return m_grades.size(); }

	MonsterGrade* GetMonsterGrade(int8 grade)
	{ return m_grades.at(grade - 1); }

	MonsterStats* GetMonsterStats(int8 grade)
	{
		try{
		return m_gradesStats.at(grade - 1);
		}catch(...) { return NULL; }
	}

	bool CanPlay() const
	{ return m_canPlay; }

	bool CanTackle() const
	{ return m_canTackle; }

	bool IsBoss() const
	{ return m_isBoss; }

	DEntityLook& GetLook()
	{ return m_look; }
};

#endif