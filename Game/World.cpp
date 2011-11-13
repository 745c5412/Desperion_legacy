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

template<> World * Singleton<World>::m_singleton = NULL;

void World::Send(DofusMessage& data)
{
	SessionsMutex.lock();
	for(SessionMap::iterator it = Sessions.begin(); it != Sessions.end(); ++it)
		it->second->Send(data);
	SessionsMutex.unlock();
}

World::World()
{
	m_maxPlayers = 0;
	m_hiCharacterGuid = 0;
}

World::~World()
{
	// les sessions sont delete par le ~io_service du Master (ce sont des shared_ptr)
	Sessions.clear();

	for(CharacterMinimalsMap::iterator it = Characters.begin(); it != Characters.end(); ++it)
		delete it->second;
	Characters.clear();

	for(ItemMap::iterator it = Items.begin(); it != Items.end(); ++it)
		delete it->second;
	Items.clear();

	for(MapMap::iterator it = Maps.begin(); it != Maps.end(); ++it)
		delete it->second;
	Maps.clear();
	
	for(ItemSetMap::iterator it = ItemSets.begin(); it != ItemSets.end(); ++it)
		delete it->second;
	ItemSets.clear();

	Desperion::sDatabase->Execute("DELETE FROM character_items WHERE owner=-1;");
}

/*void ReadData(D2oFile* file, std::string name)
{
	ValueTable& classes = file->GetClassDefs();
	for(ValueTable::iterator it = classes.begin(); it != classes.end(); ++it)
	{
		ResultPtr QR = Desperion::sDatabase->Query("SELECT COUNT(*) FROM d2o_%s;", D2oClassDefinition::FormatName(it->second.GetName()).c_str());
		if(QR)
		{
			if(QR->Fetch()[0].GetInt32() > 0)
			{
				Log::Instance().outDebug("Count not null %s, continuing ...", it->second.GetName().c_str());
				
				return;
			}
		}
		
	}

	typedef std::vector<std::pair<D2oClassDefinition, Data> > Result;
	Result result = file->ReadAllData();

	try{
		for(Result::iterator it = result.begin(); it != result.end(); ++it)
		{
			std::string insert = it->first.GetSQLInsert(D2oClassDefinition::FormatName(it->first.GetName()), it->second);
			Desperion::sDatabase->Execute(insert.c_str());
		}
	}catch(const std::exception& e)
	{
		Log::Instance().outError("Error %s while loading %s", e.what(), name.c_str());
		return;
	}
	Log::Instance().outDebug("Loaded file '%s'", name.c_str());
}

void CreateSchema()
{
	sFileAccessor.Init("d2o");
	boost::filesystem::path p("d2o/");
	boost::filesystem::directory_iterator end;
	for(boost::filesystem::directory_iterator it(p); it != end; ++it)
	{
		D2oFile* file = NULL;
		try{
			file = sFileAccessor.LoadFile(it->filename());
		}catch(const ServerError& err)
		{ std::cerr<<err.what()<<std::endl; }
		if(!file)
			continue;

		ValueTable& table = file->GetClassDefs();
		for(ValueTable::iterator it2 = table.begin(); it2 != table.end(); ++it2)
		{
			std::string name = D2oClassDefinition::FormatName(it2->second.GetName());
			std::string schema = it2->second.GetSQLSchema(name);
			Desperion::sDatabase->Execute(schema.c_str());
			Log::Instance().outDebug("Created schema %s", name.c_str());
		}
	}

	FileMap& files = sFileAccessor.GetFiles();

	boost::threadpool::pool tp(2);
	for(FileMap::iterator it = files.begin(); it != files.end(); ++it)
		tp.schedule(boost::bind(&ReadData, it->second, it->first));
	tp.wait();
}*/

void World::Init()
{
	uint32 threadcount;
#ifndef WIN32
#if UNIX_FLAVOUR == UNIX_FLAVOUR_LINUX
#ifdef X64
	threadcount = 2;
#else
	long affmask;
	sched_getaffinity(0, 4, (cpu_set_t*)&affmask);
	threadcount = (BitCount8(affmask)) * 2;
	if(threadcount > 8) threadcount = 8;
	else if(threadcount <= 0) threadcount = 1;
#endif
#else
	threadcount = 2;
#endif
#else
	SYSTEM_INFO s;
	GetSystemInfo(&s);
	threadcount = s.dwNumberOfProcessors * 2;
	if(threadcount > 8)
		threadcount = 8;
#endif

	boost::threadpool::pool tp(threadcount);
	uint32 count = 0;
	Log::Instance().outNotice("World", "Loading world...");
	tp.schedule(boost::bind(&World::LoadCharacterMinimals, this));
	tp.schedule(boost::bind(&World::LoadItemSets, this));
	tp.schedule(boost::bind(&World::LoadItems, this));
	tp.schedule(boost::bind(&World::LoadMaps, this));
	tp.wait();
	Log::Instance().outNotice("World", "World loaded!\n\n");

	Session::InitHandlersTable();
	Session::InitCommandsTable();
}

void World::LoadItems()
{
	uint32 time = getMSTime();
	ResultPtr QR = Desperion::sDatabase->Query("SELECT * FROM d2o_item;");
	if(!QR)
		return;
	do
	{
		Field* fields = QR->Fetch();
		Item* i = new Item;
		i->Init(fields);
		Items[i->GetId()] = i;
	}while(QR->NextRow());
	

	QR = Desperion::sDatabase->Query("SELECT * FROM d2o_weapon;");
	if(!QR)
		return;
	do
	{
		Field* fields = QR->Fetch();
		Weapon* w = new Weapon;
		w->Init(fields);
		Items[w->GetId()] = w;
	}while(QR->NextRow());
	

	Log::Instance().outNotice("World", "%u items loaded in %ums!", Items.size(), getMSTime() - time);
}

void World::LoadItemSets()
{
	uint32 time = getMSTime();
	ResultPtr QR = Desperion::sDatabase->Query("SELECT id, effects FROM d2o_item_set;");
	if(!QR)
		return;
	do
	{
		Field* fields = QR->Fetch();
		ItemSet* i = new ItemSet;
		i->Init(fields);
		ItemSets[i->GetId()] = i;
	}while(QR->NextRow());
	
	Log::Instance().outNotice("World", "%u item sets loaded in %ums!", ItemSets.size(), getMSTime() - time);
}

void World::LoadMaps()
{
	uint32 time = getMSTime();
	ResultPtr QR = Desperion::sDatabase->Query("SELECT * FROM maps JOIN d2o_map_position ON maps.id = d2o_map_position.id;");
	if(!QR)
		return;
	do
	{
		Field* fields = QR->Fetch();
		Map* map = new Map;
		map->Init(fields);
		Maps[map->GetId()] = map;
	}while(QR->NextRow());
	
	Log::Instance().outNotice("World", "%u maps loaded in %ums!", Maps.size(), getMSTime() - time);
}

void World::LoadCharacterMinimals()
{
	uint32 time = getMSTime();
	ResultPtr QR = Desperion::sDatabase->Query("SELECT * FROM character_minimals ORDER BY id DESC;");
	if(!QR)
		return;
	do
	{
		Field* fields = QR->Fetch();
		CharacterMinimals* ch = new CharacterMinimals;
		ch->Init(fields);
		Characters[ch->id] = ch;
	}while(QR->NextRow());
	
	m_hiCharacterGuid = Characters.begin()->second->id;

	Log::Instance().outNotice("World", "%u character minimals loaded in %ums!", Characters.size(), getMSTime() - time);
}

Map* World::GetMap(int id)
{
	Map* map = NULL;
	MapsMutex.lock();
	MapMap::iterator it = Maps.find(id);
	if(it != Maps.end())
	{
		map = it->second;
		if(!map->IsBuilt())
			map->Build();
	}
	MapsMutex.unlock();
	return map;
}

Map* World::GetMap(int16 x, int16 y)
{
	Map* map = NULL;
	MapsMutex.lock();
	for(MapMap::iterator it = Maps.begin(); it != Maps.end(); ++it)
	{
		if(it->second->GetPosX() == x && it->second->GetPosY() == y)
		{
			map = it->second;
			if(!map->IsBuilt())
				map->Build();
			break;
		}
	}
	MapsMutex.unlock();
	return map;
}

CharacterMinimals* World::GetCharacterMinimals(std::string name)
{
	CharacterMinimals* ch = NULL;
	name = Desperion::ToLowerCase(name);
	CharactersMutex.lock();
	for(CharacterMinimalsMap::iterator it = Characters.begin(); it != Characters.end(); ++it)
	{
		if(Desperion::ToLowerCase(it->second->name) == name)
		{
			ch = it->second;
			break;
		}
	}
	CharactersMutex.unlock();
	return ch;
}

void World::AddCharacterMinimals(CharacterMinimals* ch)
{
	CharactersMutex.lock();
	Characters[ch->id] = ch;
	CharactersMutex.unlock();
}

CharacterMinimals* World::GetCharacterMinimals(int guid)
{
	CharacterMinimals* ch = NULL;
	CharactersMutex.lock();
	CharacterMinimalsMap::iterator it = Characters.find(guid);
	if(it != Characters.end())
		ch = it->second;
	CharactersMutex.unlock();
	return ch;
}

void World::DeleteCharacterMinimals(int guid)
{
	CharactersMutex.lock();
	CharacterMinimalsMap::iterator it = Characters.find(guid);
	if(it != Characters.end())
		Characters.erase(it);
	CharactersMutex.unlock();
}

std::list<CharacterMinimals*> World::GetCharactersByAccount(int guid)
{
	std::list<CharacterMinimals*> result;
	CharactersMutex.lock();
	for(CharacterMinimalsMap::iterator it = Characters.begin(); it != Characters.end(); ++it)
		if(it->second->account == guid)
			result.push_back(it->second);
	CharactersMutex.unlock();
	return result;
}

Item* World::GetItem(int id)
{
	Item* i = NULL;
	ItemsMutex.lock();
	ItemMap::iterator it = Items.find(id);
	if(it != Items.end())
		i = it->second;
	ItemsMutex.unlock();
	return i;
}

ItemSet* World::GetItemSet(int16 id)
{
	ItemSet* i = NULL;
	ItemSetsMutex.lock();
	ItemSetMap::iterator it = ItemSets.find(id);
	if(it != ItemSets.end())
		i = it->second;
	ItemSetsMutex.unlock();
	return i;
}

void World::AddSession(Session* s)
{
	SessionsMutex.lock();
	Sessions[s->GetData(FLAG_GUID).intValue] = s;
	if(Sessions.size() > m_maxPlayers)
		m_maxPlayers = Sessions.size();
	SessionsMutex.unlock();
}

Session* World::GetSession(int guid)
{
	Session* s = NULL;
	SessionsMutex.lock();
	SessionMap::iterator it = Sessions.find(guid);
	if(it != Sessions.end())
		s = it->second;
	SessionsMutex.unlock();
	return s;
}

void World::DeleteSession(int guid)
{
	SessionsMutex.lock();
	SessionMap::iterator it = Sessions.find(guid);
	if(it != Sessions.end())
		Sessions.erase(it);
	SessionsMutex.unlock();
}