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

// ATTENTION: NE REGARDEZ PAS CE CODE SI VOUS NE VOULEZ PAS MOURRIR D'UN INFARCTUS!!!

#define VAR_LENGTH 2

ConditionsParser::ConditionsParser(const std::vector<int8>& emotes, const std::list<PlayerItem*>& items, std::string name) : m_playerItems(items),
	m_emotes(emotes)
{
	m_formula = "";
	m_playerName = Desperion::ToLowerCase(name);
}

void ConditionsParser::SetFormula(std::string formu)
{
	m_formula = formu;
}


bool ConditionsParser::Eval()
{
	bool isInPar = false;
	for(int a = 0; a < m_formula.size(); ++a)
	{
		switch(m_formula[a])
		{
		case '(':
			isInPar = true;
			break;
		case ')':
			isInPar = false;
			break;
		case '&':
			if(isInPar)
				m_formula[a] = '`';
			break;
		case '|':
			if(isInPar)
				m_formula[a] = '~';
			break;
		}
	}

	std::vector<std::string> table; // table "ET"
	Desperion::Split(table, m_formula, '&');
	try
	{ // début du try
		std::list<bool> ands; // liste contenant tous les résultats du table "ET"
		for(int a = 0; a < table.size(); ++a) // boucle tableau "ET"
		{
			std::string cond_and = table.at(a); // "ET" actuel
			std::vector<std::string> table2; // tableau "OU"
			Desperion::Split(table2, cond_and, '|');
			std::list<bool> ors; // liste contenant tous les résultats du tableau "OU"
			for(int b = 0; b < table2.size(); b++) // boucle tableau "OU"
			{
				std::string cond_or = table2.at(b); // "OU" actuel

				if(cond_or.at(0) == '(')
				{
					std::string par = "";
					for(int c = 1; c < cond_or.size() - 1; ++c)
						par += cond_or[c];
					ConditionsParser P(m_emotes, m_playerItems, m_playerName);
					for(std::tr1::unordered_map<std::string, int64>::iterator it = m_variables.begin(); it != m_variables.end(); ++it)
						P.AddVar(it->first, it->second);
					ors.push_back(P.Eval());
					continue;
				}
				switch(cond_or.at(2)) // switch tableau "OU"
				{
				case '<': // inférieur à
					{
						std::string var = cond_or.substr(0,2);
						std::string value = cond_or.substr(3);
						int64 ivalue;
						Desperion::FromString(value, ivalue);
						std::tr1::unordered_map<std::string, int64>::iterator it = m_variables.find(var);
						if(it == m_variables.end())
							return false;
						if(it->second < ivalue)
							ors.push_back(true);
						else
							ors.push_back(false);
					}
					break;
				case '>': // supérieur à
					{
						std::string var = cond_or.substr(0,2);
						std::string value = cond_or.substr(3);
						int64 ivalue;
						Desperion::FromString(value, ivalue);
						std::tr1::unordered_map<std::string, int64>::iterator it = m_variables.find(var);
						if(it == m_variables.end())
							return false;
						if(it->second > ivalue)
							ors.push_back(true);
						else
							ors.push_back(false);
					}
					break;
				case '~':
				case '=': // égal à
					{
						std::string var = cond_or.substr(0,2);
						std::string value = cond_or.substr(3);
						if(var == "PO")
						{
							bool have = false;
							for(std::list<PlayerItem*>::const_iterator it = m_playerItems.begin(); it != m_playerItems.end(); ++it)
							{
								if(Desperion::ToString((*it)->GetItem()->GetId()) == value)
								{
									have = true;
									break;
								}
							}
							if(have)
								ors.push_back(true);
							else
								ors.push_back(false);
							break;
						}
						else if(var == "PN")
						{
							if(m_playerName == Desperion::ToLowerCase(value))
								ors.push_back(true);
							else
								ors.push_back(false);
							break;
						}
						else if(var == "PE")
						{
							bool have = false;
							for(std::vector<int8>::const_iterator it = m_emotes.begin(); it != m_emotes.end(); ++it)
							{
								if(Desperion::ToString(*it) == value)
								{
									have = true;
									break;
								}
							}
							if(have)
								ors.push_back(true);
							else
								ors.push_back(false);
							break;
						}
						std::tr1::unordered_map<std::string, int64>::iterator it = m_variables.find(var);
						if(it == m_variables.end())
							return false;
						if(Desperion::ToString(it->second) == value)
							ors.push_back(true);
						else
							ors.push_back(false);
					}
					break;
				case 'X':
				case '!': // n'est pas égal à
					{
						std::string var = cond_or.substr(0,2);
						std::string value = cond_or.substr(3);
						if(var == "PO")
						{
							bool have = false;
							for(std::list<PlayerItem*>::const_iterator it = m_playerItems.begin(); it != m_playerItems.end(); ++it)
							{
								if(Desperion::ToString((*it)->GetItem()->GetId()) == value)
								{
									have = true;
									break;
								}
							}
							if(!have)
								ors.push_back(true);
							else
								ors.push_back(false);
							break;
						}
						else if(var == "PN")
						{
							if(m_playerName != Desperion::ToLowerCase(value))
								ors.push_back(true);
							else
								ors.push_back(false);
							break;
						}
						else if(var == "PE")
						{
							bool have = false;
							for(std::vector<int8>::const_iterator it = m_emotes.begin(); it != m_emotes.end(); ++it)
							{
								if(Desperion::ToString(*it) == value)
								{
									have = true;
									break;
								}
							}
							if(!have)
								ors.push_back(true);
							else
								ors.push_back(false);
							break;
						}
						std::tr1::unordered_map<std::string, int64>::iterator it = m_variables.find(var);
						if(it == m_variables.end())
							return false;
						if(Desperion::ToString(it->second) != value)
							ors.push_back(true);
						else
							ors.push_back(false);
					}
					break;
				default:
					return false;
				} // fin switch table "OU"
			} // fin boucle "OU"

			bool exists = false;
			for(std::list<bool>::iterator it = ors.begin(); it != ors.end(); ++it)
			{
				if((*it))
					exists = true;
			}
			ands.push_back(exists);

		} // fin boucle "ET"

		for(std::list<bool>::iterator it = ands.begin(); it != ands.end(); ++it)
		{
			if(!(*it))
				return false;
		}

	}catch(const std::exception&)
	{
		return false;
	}
	return true;
}

void ConditionsParser::AddVar(std::string name, int64 value)
{
	if(name.size() != VAR_LENGTH)
		name = name.substr(0,2);
	m_variables[name] = value;
}