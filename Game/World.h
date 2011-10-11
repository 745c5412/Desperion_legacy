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

#ifndef __WORLD__
#define __WORLD__

class Session;
class Item;
struct CharacterMinimals;
class Map;

typedef boost::mutex Mutex;

class World : public Singleton<World>
{
public:
	typedef std::set<Session*> SessionSet;
	typedef std::tr1::unordered_map<int, CharacterMinimals*> CharacterMinimalsMap;
	typedef std::tr1::unordered_map<int, Item*> ItemMap;
	typedef std::tr1::unordered_map<int, Map*> MapMap;

	World();
	~World();
	void Init();
	void Update();
	//void CreateSchema();

	void LoadCharacterMinimals();
	void LoadItems();
	void LoadMaps();

	void AddSession(Session*);
	void DeleteSession(Session*);
	Session* GetSession(uint32);

	Map* GetMap(int);
	Map* GetMapByCoords(int16, int16);

	void AddCharacterMinimals(CharacterMinimals*);
	CharacterMinimals* GetCharacterMinimals(int);
	void DeleteCharacterMinimals(int);
	std::list<CharacterMinimals*> GetCharactersByAccount(int);

	int GetNextCharacterGuid()
	{
		int guid = 0;
		HiCharacterGuidMutex.lock();
		guid = ++m_hiCharacterGuid;
		HiCharacterGuidMutex.unlock();
		return guid;
	}

	Item* GetItem(int);

	uint16 GetPlayers() const
	{ return Sessions.size(); }

	uint16 GetMaxPlayers() const
	{ return m_maxPlayers; }

	const SessionSet& GetSessions() const
	{ return Sessions; }
private:
	SessionSet Sessions;
	CharacterMinimalsMap Characters;
	ItemMap Items;
	MapMap Maps;

	uint16 m_maxPlayers;

	int m_hiCharacterGuid;
	Mutex HiCharacterGuidMutex;

	Mutex MapsMutex;
	Mutex SessionsMutex;
	Mutex CharactersMutex;
	Mutex ItemsMutex;
};

#endif