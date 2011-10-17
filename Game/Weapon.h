/*
	This file is part of Desperion.
	Copyright 2010, 2011 LittleScaraby

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

#ifndef __WEAPON__
#define __WEAPON__

class Weapon : public Item
{
public:
	Weapon() {}
	void Init(Field*);

	bool IsWeapon() const
	{ return true; }
private:
	int m_range;
	int m_criticalHitBonus;
	int m_minRange;
	bool m_castTestLos;
	int m_criticalFailureProbability;
	int m_criticalHitProbability;
	int m_apCost;
	bool m_castInLine;
};

#endif