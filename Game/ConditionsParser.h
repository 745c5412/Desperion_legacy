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

#ifndef __CONDITIONS_PARSER__
#define __CONDITIONS_PARSER__

class PlayerItem;

class ConditionsParser
{
public:
	ConditionsParser(const std::list<PlayerItem*>&, std::string);
	bool Eval();
	void AddVar(std::string, int64);
	void SetFormula(std::string);
private:
	std::string m_formula;
	std::tr1::unordered_map<std::string, int64> m_variables;
	const std::list<PlayerItem*>& m_playerItems;
	std::string m_playerName;
};

#endif