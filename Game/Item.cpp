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

void Item::Init(Field* fields)
{
	m_id = fields[0].GetInt16();
	m_typeId = fields[2].GetInt32();
	m_level = fields[5].GetInt32();
	m_weight = fields[6].GetInt32();
	m_cursed = fields[7].GetBool();
	m_useAnimationId = fields[8].GetInt32();
	m_usable = fields[9].GetBool();
	m_targetable = fields[10].GetBool();
	m_price = fields[11].GetInt32();
	m_twoHanded = fields[12].GetBool();
	m_etheral = fields[13].GetBool();
	m_itemSetId = fields[14].GetInt32();
	m_criteria = fields[15].GetString();
	m_appearanceId = fields[17].GetInt32();
	Desperion::FastSplit<';'>(m_possibleEffects, std::string(fields[20].GetString()), F);
	Desperion::FastSplit<','>(m_favoriteSubAreas, std::string(fields[21].GetString()), Desperion::SplitInt);
	m_favoriteSubAreaBonus = fields[22].GetInt32();
}