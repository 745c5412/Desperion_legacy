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

Monster::~Monster()
{
	for(size_t a = 0; a < m_grades.size(); ++a)
		delete m_grades[a];
	for(size_t a = 0; a < m_gradesStats.size(); ++a)
		delete m_gradesStats[a];
}
void Monster::Init(Field* fields)
{
	m_id = fields[0].GetInt32();
	m_gfxId = fields[1].GetInt32();
	m_race = fields[2].GetInt32();
	Desperion::FastSplit<';'>(m_grades, std::string(fields[3].GetString()), &M);
	m_look.Init(fields[4].GetString());
	m_canPlay = fields[5].GetBool();
	m_canTackle = fields[6].GetBool();
	m_isBoss = fields[7].GetBool();
	Desperion::FastSplit<';'>(m_gradesStats, std::string(fields[8].GetString()), &MS);
	m_minRespawnTime = fields[9].GetInt64();
}