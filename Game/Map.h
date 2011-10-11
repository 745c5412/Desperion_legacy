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

#ifndef __MAP__
#define __MAP__

#define ToCharacter(X) ((Character*)X)

class DisplayableEntity;

class Map
{
public:
	void Init(Field*);
	DisplayableEntity* GetActor(int);
	void AddActor(DisplayableEntity*);
	void RemoveActor(int);

	int GetId() const
	{ return m_id; }

	int16 GetPosX() const
	{ return m_posX; }

	int16 GetPosY() const
	{ return m_posY; }

	int16 GetSubareaId() const
	{ return m_subareaId; }

	int GetCapabilities() const
	{ return m_capabilities; }

	std::list<DisplayableEntity*>& GetActors()
	{ return m_actors; }
private:
	int m_id;
	int16 m_posX;
	int16 m_posY;
	int16 m_subareaId;
	int m_capabilities;
	std::list<DisplayableEntity*> m_actors;
};

#endif