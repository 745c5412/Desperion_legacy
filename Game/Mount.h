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

#ifndef __MOUNT__
#define __MOUNT__

struct MountData
{
	std::vector<std::pair<int, double> > stats;
	int stade;
	int itemId;
	int scrollId;
};

class Mount
{
public:
	Mount();
	void Init(Field*);
	~Mount();
	static Mount* Create(uint8, uint8, std::string, std::string, uint16, uint32);

	static void InsertIntoDB(Mount*);
	void Save();

	void SetMountPark(int m)
	{ m_mountPark = m; }

	int GetMountPark() const
	{ return m_mountPark; }

	bool IsCastrated() const
	{ return m_castrated; }

	void SetCastrated(bool c)
	{ m_castrated = c; }

	uint64 GetId() const
	{ return m_id; }

	int GetModel() const
	{ return m_model; }

	uint8 GetSex() const
	{ return m_sex; }

	std::string GetName() const
	{ return m_name; }

	void SetName(std::string n)
	{ m_name = n; }

	int GetReproductions() const
	{ return m_reproductions; }

	void SetReproductions(int r)
	{ m_reproductions = r; }

	time_t GetGestation() const
	{ return m_gestation; }

	void SetGestation(time_t g)
	{ m_gestation = g; }

	uint8 GetTiredness() const
	{ return m_tiredness; }

	void SetTiredness(uint8 t)
	{ m_tiredness = t; }

	int GetStamina() const
	{ return m_stamina; }

	void SetStamina(int s)
	{ m_stamina = s; }

	int GetLove() const
	{ return m_love; }

	void SetLove(int l)
	{ m_love = l; }

	int GetMaturity() const
	{ return m_maturity; }

	void SetMaturity(int m)
	{ m_maturity = m; }

	int GetEnergy() const
	{ return m_energy; }

	void SetEnergy(int e)
	{ m_energy = e; }

	int GetSerenity() const
	{ return m_serenity; }

	void SetSerenity(int s)
	{ m_serenity = s; }

	const std::vector<int>& GetAncestors() const
	{ return m_ancestors; }

	const std::list<PlayerItem*>& GetItems()
	{ return m_items; }

	std::string GetCapabilitiesString();

	const std::vector<int>& GetBehaviors()
	{ return m_behaviors; }

	int GetOwnerId() const
	{ return m_ownerId; }

	int GetPodsUsed();

	bool HasBehavior(int);
	bool IsFertile();
	bool IsRideable();
	static std::tr1::unordered_map<std::string, uint16> GetCaracteristics(uint8, uint16);
private:
	bool m_castrated;
	uint64 m_id;
	int m_model;
	bool m_sex;
	std::string m_name;
	int m_reproductions;
	time_t m_gestation;
	uint8 m_tiredness;

	int m_stamina;
	int m_love;
	int m_maturity;
	int m_energy;
	
	int m_serenity;
	int m_mountPark;

	std::vector<int> m_ancestors;
	std::list<PlayerItem*> m_items;
	std::vector<int> m_behaviors;
	int m_ownerId;
};

#endif