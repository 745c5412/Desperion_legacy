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

#ifndef __DOFUS_UTILS__
#define __DOFUS_UTILS__

class Session;

namespace DofusUtils
{
	int16 GetObviAppearanceBySkinId(int, int);
	uint8 GetLevelByObviXp(int);
	bool CheckName(std::string name);
	void FillParser(ConditionsParser&, Session*, bool full = true);
	void LoopItemConditions(ConditionsParser&, Session*);
	bool IsValidPlaceForItem(const Item*, uint8);
}

#endif