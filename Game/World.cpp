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
	boost::mutex::scoped_lock lock(SessionsMutex);
	for(SessionMap::iterator it = Sessions.begin(); it != Sessions.end(); ++it)
		it->second->Send(data);
}

World::World()
{
	m_maxPlayers = 0;
	m_hiCharacterGuid = 0;
}

void World::SaveAll()
{
	boost::mutex::scoped_lock lock(SessionsMutex);
	for(SessionMap::iterator it = Sessions.begin(); it != Sessions.end(); ++it)
	{
		if(it->second->GetData(FLAG_GUID).intValue != 0)
		{
			it->second->Save();
			if(it->second->GetCharacter() != NULL)
				it->second->GetCharacter()->Save();
		}
	}
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
	boost::threadpool::pool tp(boost::thread::hardware_concurrency() + 1);
	Log::Instance().outNotice("World", "Loading world...");
	tp.schedule(boost::bind(&World::LoadSubareas, this));
	tp.wait();
	tp.schedule(boost::bind(&World::LoadCharacterMinimals, this));
	tp.schedule(boost::bind(&World::LoadItemSets, this));
	tp.schedule(boost::bind(&World::LoadItems, this));
	tp.schedule(boost::bind(&World::LoadMaps, this));
	tp.wait();
	Log::Instance().outNotice("World", "World loaded!\n\n");

	Session::InitHandlersTable();
	Session::InitCommandsTable();
}

void World::LoadSubareas()
{
	uint32 time = getMSTime();
	ResultPtr QR = Desperion::sDatabase->Query("SELECT d2o_sub_area.id, areaId, mapIds, sub_area_spawns.spawns FROM d2o_sub_area JOIN sub_area_spawns ON \
											   d2o_sub_area.id=sub_area_spawns.id;");
	if(!QR)
		return;
	do
	{
		Field* fields = QR->Fetch();
		Subarea* s = new Subarea;
		s->Init(fields);
		std::vector<int> maps;
		Desperion::FastSplit<','>(maps, std::string(fields[2].GetString()), Desperion::SplitInt);
		Subareas[s->GetId()] = s;
	}while(QR->NextRow());

	Log::Instance().outNotice("World", "%u subareas loaded in %ums!", Subareas.size(), getMSTime() - time);
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
		if(map->GetSubareaId() > 0)
			Subareas[map->GetSubareaId()]->AddMap(map);
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
	boost::mutex::scoped_lock lock(MapsMutex);
	MapMap::iterator it = Maps.find(id);
	if(it != Maps.end())
	{
		map = it->second;
		if(!map->IsBuilt())
			map->Build();
	}
	return map;
}

Map* World::GetMap(int16 x, int16 y)
{
	Map* map = NULL;
	boost::mutex::scoped_lock lock(MapsMutex);
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
	return map;
}

CharacterMinimals* World::GetCharacterMinimals(std::string name)
{
	CharacterMinimals* ch = NULL;
	name = Desperion::ToLowerCase(name);
	boost::mutex::scoped_lock lock(CharactersMutex);
	for(CharacterMinimalsMap::iterator it = Characters.begin(); it != Characters.end(); ++it)
	{
		if(Desperion::ToLowerCase(it->second->name) == name)
		{
			ch = it->second;
			break;
		}
	}
	return ch;
}

void World::AddCharacterMinimals(CharacterMinimals* ch)
{
	boost::mutex::scoped_lock lock(CharactersMutex);
	Characters[ch->id] = ch;
}

CharacterMinimals* World::GetCharacterMinimals(int guid)
{
	CharacterMinimals* ch = NULL;
	boost::mutex::scoped_lock lock(CharactersMutex);
	CharacterMinimalsMap::iterator it = Characters.find(guid);
	if(it != Characters.end())
		ch = it->second;
	return ch;
}

void World::DeleteCharacterMinimals(int guid)
{
	boost::mutex::scoped_lock lock(CharactersMutex);
	CharacterMinimalsMap::iterator it = Characters.find(guid);
	if(it != Characters.end())
		Characters.erase(it);
}

std::list<CharacterMinimals*> World::GetCharactersByAccount(int guid)
{
	std::list<CharacterMinimals*> result;
	boost::mutex::scoped_lock lock(CharactersMutex);
	for(CharacterMinimalsMap::iterator it = Characters.begin(); it != Characters.end(); ++it)
		if(it->second->account == guid)
			result.push_back(it->second);
	return result;
}

Item* World::GetItem(int id)
{
	Item* i = NULL;
	boost::mutex::scoped_lock lock(ItemsMutex);
	ItemMap::iterator it = Items.find(id);
	if(it != Items.end())
		i = it->second;
	return i;
}

ItemSet* World::GetItemSet(int16 id)
{
	ItemSet* i = NULL;
	boost::mutex::scoped_lock lock(ItemSetsMutex);
	ItemSetMap::iterator it = ItemSets.find(id);
	if(it != ItemSets.end())
		i = it->second;
	return i;
}

void World::AddSession(Session* s)
{
	boost::mutex::scoped_lock lock(SessionsMutex);
	Sessions[s->GetData(FLAG_GUID).intValue] = s;
	if(Sessions.size() > m_maxPlayers)
		m_maxPlayers = Sessions.size();
}

Session* World::GetSession(int guid)
{
	Session* s = NULL;
	boost::mutex::scoped_lock lock(SessionsMutex);
	SessionMap::iterator it = Sessions.find(guid);
	if(it != Sessions.end())
		s = it->second;
	return s;
}

Session* World::GetSession(std::string pseudo)
{
	pseudo = Desperion::ToLowerCase(pseudo);
	Session* s= NULL;
	boost::mutex::scoped_lock lock(SessionsMutex);
	for(SessionMap::iterator it = Sessions.begin(); it != Sessions.end(); ++it)
	{
		if(Desperion::ToLowerCase(it->second->GetData(FLAG_PSEUDO).stringValue) == pseudo)
		{
			s = it->second;
			break;
		}
	}
	return s;
}

void World::DeleteSession(int guid)
{
	boost::mutex::scoped_lock lock(SessionsMutex);
	SessionMap::iterator it = Sessions.find(guid);
	if(it != Sessions.end())
		Sessions.erase(it);
}