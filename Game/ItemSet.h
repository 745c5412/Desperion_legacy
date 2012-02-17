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

#ifndef __ITEM_SET__
#define __ITEM_SET__

/*inline EffectInstanceInteger* I(std::string& str)
{
	std::vector<int> table;
	Desperion::FastSplit<','>(table, str, Desperion::SplitInt);
	return new EffectInstanceInteger(table[2], table[0], table[3], table[4], table[1] == 1,
		table[5], table[7], table[6]);
}*/

inline std::vector<PlayerItemEffect*> H(std::string& str)
{
	std::vector<PlayerItemEffect*> table;
	Desperion::FastSplit<';'>(table, str, G);
	return table;
}

class ItemSet
{
public:
	typedef std::vector<std::vector<PlayerItemEffect*> > SetEffectsMap;
private:
	int16 m_id;
	SetEffectsMap m_effects;
	std::vector<PlayerItemEffect*> m_empty; // pour la reference constante de GetEffect (cf implementation)
public:
	void Init(Field*);
	~ItemSet();
	const std::vector<PlayerItemEffect*>& GetEffect(uint8) const;
	static void ApplyEffects(Character*, const std::vector<PlayerItemEffect*>&, bool);

	int16 GetId() const
	{ return m_id; }

	const SetEffectsMap& GetEffects() const
	{ return m_effects; }
};

#endif