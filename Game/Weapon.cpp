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

#include "StdAfx.h"

void Weapon::Init(Field* fields)
{
	m_id = fields[10].GetInt16();
	m_typeId = fields[30].GetInt32();
	m_level = fields[12].GetInt32();
	m_weight = fields[1].GetInt32();
	m_cursed = fields[11].GetBool();
	m_useAnimationId = fields[28].GetInt32();
	m_usable = fields[25].GetBool();
	m_targetable = fields[17].GetBool();
	m_price = fields[23].GetInt32();
	m_twoHanded = fields[20].GetBool();
	m_etheral = fields[8].GetBool();
	m_itemSetId = fields[21].GetInt32();
	m_criteria = fields[18].GetString();
	m_appearanceId = fields[9].GetInt32();
	Desperion::FastSplit<';'>(m_possibleEffects, std::string(fields[27].GetString()), F);
	Desperion::FastSplit<','>(m_favoriteSubAreas, std::string(fields[14].GetString()), Desperion::SplitInt);
	m_favoriteSubAreaBonus = fields[0].GetInt32();
	m_range = fields[2].GetInt32();
	m_criticalHitBonus = fields[4].GetInt32();
	m_minRange = fields[5].GetInt32();
	m_castTestLos = fields[13].GetBool();
	m_criticalFailureProbability = fields[15].GetInt32();
	m_criticalHitProbability = fields[19].GetInt32();
	m_apCost = fields[24].GetInt32();
	m_castInLine = fields[26].GetBool();
}