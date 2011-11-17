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
class ItemSet;

typedef boost::mutex Mutex;

class World : public Singleton<World>
{
public:
	typedef std::tr1::unordered_map<int, Session*> SessionMap;
	typedef std::tr1::unordered_map<int, CharacterMinimals*> CharacterMinimalsMap;
	typedef std::tr1::unordered_map<int, Item*> ItemMap;
	typedef std::tr1::unordered_map<int, Map*> MapMap;
	typedef std::tr1::unordered_map<int16, ItemSet*> ItemSetMap;

	World();
	~World();
	void Init();
	void SaveAll();

	void LoadCharacterMinimals();
	void LoadItems();
	void LoadMaps();
	void LoadItemSets();

	void AddSession(Session*);
	void DeleteSession(int);
	Session* GetSession(int);
	void Send(DofusMessage&);

	Map* GetMap(int);
	Map* GetMap(int16, int16);

	void AddCharacterMinimals(CharacterMinimals*);
	CharacterMinimals* GetCharacterMinimals(int);
	CharacterMinimals* GetCharacterMinimals(std::string);
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
	ItemSet* GetItemSet(int16);

	uint16 GetPlayers() const
	{ return Sessions.size(); }

	uint16 GetMaxPlayers() const
	{ return m_maxPlayers; }

	const SessionMap& GetSessions() const
	{ return Sessions; }
private:
	SessionMap Sessions;
	CharacterMinimalsMap Characters;
	ItemMap Items;
	MapMap Maps;
	ItemSetMap ItemSets;

	uint16 m_maxPlayers;

	int m_hiCharacterGuid;
	Mutex HiCharacterGuidMutex;

	Mutex ItemSetsMutex;
	Mutex MapsMutex;
	Mutex SessionsMutex;
	Mutex CharactersMutex;
	Mutex ItemsMutex;
};

#endif