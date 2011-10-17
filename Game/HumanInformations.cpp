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

HumanInformations::HumanInformations(HumanEntity* ent)
{
	const std::vector<DEntityLook>& followers = ent->GetFollowingCharacters();
	uint16 size = followers.size();
	m_buffer<<size;
	for(uint16 a = 0; a < size; ++a)
		m_buffer<<followers[a].Serialize(-1);
	m_buffer<<ent->GetCurrentEmote()<<ent->GetEmoteStartTime();
	m_buffer<<ActorRestrictionsInformations(ent);
	m_buffer<<ent->GetTitle()<<ent->GetTitleParams();
}