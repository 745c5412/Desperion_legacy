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

#ifndef __GAME_CONTEXT_ACTOR_INFORMATIONS__
#define __GAME_CONTEXT_ACTOR_INFORMATIONS__

class DisplayableEntity;
class NamedEntity;
class HumanEntity;
class Character;

class GameContextActorInformations : public DofusModel
{
public:
	// todo: IDENTIFIED_DISPOSITION_INFORMATIONS
	virtual uint16 GetProtocol() const
	{ return GAME_CONTEXT_ACTOR_INFORMATIONS; }

	GameContextActorInformations(DisplayableEntity* ent, Character* ch);
	GameContextActorInformations(DisplayableEntity* ent);
};

#endif