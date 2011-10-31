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

void ItemSet::Init(Field* fields)
{
	m_id = fields[0].GetInt16();
	Desperion::FastSplit<':'>(m_effects, std::string(fields[1].GetString()), H);
}

const std::vector<EffectInstance*>& ItemSet::GetEffect(uint8 pos) const
{
	try
	{ 
		 /* pos - 2: premier decalage du fait que le premier index d'un tableau
		    commence à 0, et le deuxième du fait que les bonus de panoplie ne
			commencent qu'à partir de deux objets */
		return m_effects.at(pos - 2);
	}catch(const std::out_of_range&)
	{ 
		return m_empty; 
	}
}

ItemSet::~ItemSet()
{
	for(SetEffectsMap::iterator it = m_effects.begin(); it != m_effects.end(); ++it)
		for(std::vector<EffectInstance*>::iterator it2 = it->begin(); it2 != it->end(); ++it2)
			delete *it2;
}

void ItemSet::ApplyEffects(Character* ch, const std::vector<EffectInstance*>& effects, bool add)
{
	for(std::vector<EffectInstance*>::const_iterator it = effects.begin(); it != effects.end(); ++it)
	{
		if((*it)->IsInteger())
		{
			const EffectInstanceInteger* e = (const EffectInstanceInteger*)(*it);
			ch->ApplyEffect(&StatsRow::objects, (*it)->effectId, e->value, add);
		}
	}
}