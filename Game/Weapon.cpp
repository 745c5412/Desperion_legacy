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
	_Init(fields[10].GetInt32(), fields[30].GetInt32(), fields[12].GetInt32(), fields[1].GetInt32(), fields[11].GetBool(),
		fields[28].GetInt32(), fields[25].GetBool(), fields[17].GetBool(), fields[23].GetInt32(), fields[20].GetBool(),
		fields[8].GetBool(), fields[21].GetInt32(), fields[18].GetString(), fields[9].GetInt32(), fields[27].GetString(),
		fields[14].GetString(), fields[0].GetInt32());
	m_range = fields[2].GetInt32();
	m_criticalHitBonus = fields[4].GetInt32();
	m_minRange = fields[5].GetInt32();
	m_castTestLos = fields[13].GetBool();
	m_criticalFailureProbability = fields[15].GetInt32();
	m_criticalHitProbability = fields[19].GetInt32();
	m_apCost = fields[24].GetInt32();
	m_castInLine = fields[26].GetBool();
}