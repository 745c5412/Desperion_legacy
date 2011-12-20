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

#include "StdAfx.h"

void Weapon::Init(Field* fields)
{
	Item::Init(fields);
	m_range = fields[17].GetInt32();
	m_criticalHitBonus = fields[18].GetInt32();
	m_minRange = fields[19].GetInt32();
	m_castTestLos = fields[20].GetBool();
	m_criticalFailureProbability = fields[21].GetInt32();
	m_criticalHitProbability = fields[22].GetInt32();
	m_apCost = fields[23].GetInt32();
	m_castInLine = fields[24].GetBool();
}