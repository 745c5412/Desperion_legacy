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

void World::Send(const DofusMessage& data, bool admin)
{
	boost::shared_lock<boost::shared_mutex> lock(SessionsMutex);
	for(SessionMap::iterator it = Sessions.begin(); it != Sessions.end(); ++it)
		if(!admin || it->second->GetData(FLAG_LEVEL).intValue > 0)
			it->second->Send(data);
}

void World::SaveAll() // à n'utiliser qu'en cas de crash
{
	for(SessionMap::iterator it = Sessions.begin(); it != Sessions.end(); ++it)
	{
		if(it->second->GetData(FLAG_GUID).intValue != 0)
		{
			it->second->Save();
			if(it->second->GetData(FLAG_GUID).intValue != 0)
			{
				Desperion::eDatabase->Execute("UPDATE accounts SET logged=0 WHERE guid=%u;",
					it->second->GetData(FLAG_GUID).intValue);
			}
		}
	}
}

World::~World()
{
	for(SessionMap::iterator it = Sessions.begin(); it != Sessions.end(); ++it)
	{
		delete it->second->GetParty();
		it->second->SetParty(NULL);
	}
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

	for(SubAreaMap::iterator it = SubAreas.begin(); it != SubAreas.end(); ++it)
		delete it->second;
	SubAreas.clear();

	for(MonsterMap::iterator it = Monsters.begin(); it != Monsters.end(); ++it)
		delete it->second;
	Monsters.clear();

	Desperion::sDatabase->Execute("DELETE FROM \"character_items\" WHERE \"owner\"=-1;");
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
				Log::Instance().OutDebug("Count not null %s, continuing ...", it->second.GetName().c_str());
				
				return;
			}
		}
		
	}

	typedef std::vector<std::pair<D2oClassDefinition, Data> > Result;
	Result result = file->ReadAllData();

	try{
		Log::Instance().OutDebug("Loading file '%s'", name.c_str());
		for(Result::iterator it = result.begin(); it != result.end(); ++it)
		{
			std::string insert = it->first.GetSQLInsert(D2oClassDefinition::FormatName(it->first.GetName()), it->second);
			Desperion::sDatabase->Execute(insert.c_str());
		}
	}catch(const std::exception& e)
	{
		Log::Instance().OutError("Error %s while loading %s", e.what(), name.c_str());
		return;
	}
	Log::Instance().OutDebug("Loaded file '%s'", name.c_str());
}

void CreateSchema()
{
	new D2oFileAccessor;
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
			Log::Instance().OutDebug("Created schema %s", name.c_str());
		}
	}

	FileMap& files = sFileAccessor.GetFiles();

	boost::threadpool::pool tp(2);
	for(FileMap::iterator it = files.begin(); it != files.end(); ++it)
		tp.schedule(boost::bind(&ReadData, it->second, it->first));
	tp.wait();
	delete D2oFileAccessor::InstancePtr();
}*/

void World::Init()
{
	boost::threadpool::pool tp(boost::thread::hardware_concurrency());
	Log::Instance().OutNotice("World", "Loading world...");
	tp.schedule(boost::bind(&World::LoadSubAreas, this));
	tp.wait();
	tp.schedule(boost::bind(&World::LoadCharacterMinimals, this));
	tp.schedule(boost::bind(&World::LoadItemSets, this));
	tp.schedule(boost::bind(&World::LoadItems, this));
	tp.schedule(boost::bind(&World::LoadMaps, this));
	tp.schedule(boost::bind(&World::LoadMonsters, this));
	tp.wait();
	SpawnMonsters();

	ResultPtr QR = Desperion::sDatabase->Query("SELECT \"guid\" FROM \"character_items\" ORDER BY \"guid\" DESC LIMIT 1;");
	if(QR)
	{
		QR->NextRow();
		m_hiCharacterGuid = (QR->Fetch()[0].GetInt32()) + 1;
	}

	Log::Instance().OutNotice("World", "World loaded!\n\n");

	Session::InitHandlersTable();
	Session::InitCommandsTable();
}

void World::SpawnMonsters()
{
	Log::Instance().OutNotice("World", "Spawning monsters...");
	uint32 time = getMSTime();

	struct stream
	{
		SubAreaMap::iterator it;

		bool pop_if_present(SubAreaMap::iterator& it)
		{
			if(this->it != World::Instance().SubAreas.end())
			{
				it = this->it;
				++(this->it);
				return true;
			}
			else
				return false;
		}

		stream() : it(World::Instance().SubAreas.begin())
		{
		}
	};
	struct apply
	{
		typedef SubAreaMap::iterator argument_type; 

		void operator()(SubAreaMap::iterator it) const
		{
			if(!it->second->GetPossibleSpawns().empty())
			{
				std::list<Map*>& maps = it->second->GetMaps();
				time_t now = ::time(NULL);
				for(std::list<Map*>::iterator it2 = maps.begin(); it2 != maps.end(); ++it2)
					if((*it2)->SpawnSubAreaMonsters())
						(*it2)->SpawnMonsters(it->second, now);
			}
		}
	};

	tbb::parallel_while<apply> w;
	stream s;
	apply a;
	w.run(s, a);
	Log::Instance().OutNotice("World", "Monsters spawned in %ums!", getMSTime() - time);
}

void World::LoadMonsters()
{
	uint32 time = getMSTime();
	ResultPtr QR = Desperion::sDatabase->Query("SELECT \"id\", \"gfxId\", \"race\", \"grades\", \"look\", \"canPlay\", \"canTackle\", \
											   \"isBoss\", \"monster_stats\".\"stats\", \"monster_stats\".\"minRespawnTime\" FROM \
											   \"d2o_monster\" JOIN \"monster_stats\" ON \"d2o_monster\".\"id\"=\"monster_stats\".\"monsterId\";");
	if(!QR)
		return;
	while(QR->NextRow())
	{
		Field* fields = QR->Fetch();
		Monster* m = new Monster;
		std::tr1::unordered_map<int, std::string>::value_type;
		m->Init(fields);
		Monsters[m->GetId()] = m;
	}

	Log::Instance().OutNotice("World", "%u monsters loaded in %ums!", Monsters.size(), getMSTime() - time);
}

void World::LoadSubAreas()
{
	uint32 time = getMSTime();
	ResultPtr QR = Desperion::sDatabase->Query("SELECT \"d2o_sub_area\".\"id\", \"areaId\", \"sub_area_spawns\".\"spawns\" \
											   FROM \"d2o_sub_area\" JOIN \"sub_area_spawns\" ON \"d2o_sub_area\".\"id\"=\"sub_area_spawns\".\"id\";");
	if(!QR)
		return;
	while(QR->NextRow())
	{
		Field* fields = QR->Fetch();
		SubArea* s = new SubArea;
		s->Init(fields);
		SubAreas[s->GetId()] = s;
	}

	Log::Instance().OutNotice("World", "%u subareas loaded in %ums!", SubAreas.size(), getMSTime() - time);
}

void World::LoadItems()
{
	uint32 time = getMSTime();
	ResultPtr QR = Desperion::sDatabase->Query("SELECT \"id\", \"typeId\", \"level\", \"realWeight\", \"cursed\", \"useAnimationId\", \"usable\", \"targetable\", \"price\", \
											  \"twoHanded\", \"etheral\", \"itemSetId\", \"criteria\", \"appearanceId\", \"possibleEffects\", \"favoriteSubAreas\", \
											  \"favoriteSubAreasBonus\" FROM \"d2o_item\";");
	if(!QR)
		return;
	while(QR->NextRow())
	{
		Field* fields = QR->Fetch();
		Item* i = new Item;
		i->Init(fields);
		Items[i->GetId()] = i;
	}
	
	QR = Desperion::sDatabase->Query("SELECT \"id\", \"typeId\", \"level\", \"realWeight\", \"cursed\", \"useAnimationId\", \"usable\", \"targetable\", \"price\", \"twoHanded\", \
									\"etheral\", \"itemSetId\", \"criteria\", \"appearanceId\", \"possibleEffects\", \"favoriteSubAreas\", \"favoriteSubAreasBonus\", \
									\"range\", \"criticalHitBonus\", \"minRange\", \"castTestLos\", \"criticalFailureProbability\", \"criticalHitProbability\", \
									\"apCost\", \"castInLine\" FROM \"d2o_weapon\";");
	if(!QR)
		return;
	while(QR->NextRow())
	{
		Field* fields = QR->Fetch();
		Weapon* w = new Weapon;
		w->Init(fields);
		Items[w->GetId()] = w;
	}

	Log::Instance().OutNotice("World", "%u items loaded in %ums!", Items.size(), getMSTime() - time);
}

void World::LoadItemSets()
{
	uint32 time = getMSTime();
	ResultPtr QR = Desperion::sDatabase->Query("SELECT \"id\", \"effects\" FROM \"d2o_item_set\";");
	if(!QR)
		return;
	while(QR->NextRow())
	{
		Field* fields = QR->Fetch();
		ItemSet* i = new ItemSet;
		i->Init(fields);
		ItemSets[i->GetId()] = i;
	}
	
	Log::Instance().OutNotice("World", "%u item sets loaded in %ums!", ItemSets.size(), getMSTime() - time);
}

void World::LoadMaps()
{
	uint32 time = getMSTime();
	ResultPtr QR = Desperion::sDatabase->Query("SELECT \"maps\".*, \"posX\", \"posY\", \"capabilities\", \"subAreaId\" FROM \"maps\" \
											   JOIN \"d2o_map_position\" ON \"maps\".\"id\" = \"d2o_map_position\".\"id\";");
	if(!QR)
		return;
	while(QR->NextRow())
	{
		Field* fields = QR->Fetch();
		Map* map = new Map;
		map->Init(fields);
		Maps[map->GetId()] = map;
		if(map->GetSubAreaId() > 0)
			SubAreas[map->GetSubAreaId()]->AddMap(map);
	}
	
	Log::Instance().OutNotice("World", "%u maps loaded in %ums!", Maps.size(), getMSTime() - time);
}

void World::LoadCharacterMinimals()
{
	uint32 time = getMSTime();
	ResultPtr QR = Desperion::sDatabase->Query("SELECT * FROM \"character_minimals\" ORDER BY \"id\" DESC;");
	if(!QR)
		return;
	while(QR->NextRow())
	{
		Field* fields = QR->Fetch();
		CharacterMinimals* ch = new CharacterMinimals;
		ch->Init(fields);
		Characters[ch->id] = ch;
	}
	
	m_hiCharacterGuid = Characters.begin()->second->id;

	Log::Instance().OutNotice("World", "%u character minimals loaded in %ums!", Characters.size(), getMSTime() - time);
}

Map* World::GetMap(int id)
{
	MapMap::iterator it = Maps.find(id);
	if(it != Maps.end())
		return it->second;
	return NULL;
}

Monster* World::GetMonster(int id)
{
	MonsterMap::iterator it = Monsters.find(id);
	if(it != Monsters.end())
		return it->second;
	return NULL;
}

Map* World::GetMap(int16 x, int16 y)
{
	for(MapMap::iterator it = Maps.begin(); it != Maps.end(); ++it)
		if(it->second->GetPosX() == x && it->second->GetPosY() == y)
			return it->second;
	return NULL;
}

CharacterMinimals* World::GetCharacterMinimals(std::string name)
{
	name = Desperion::ToLowerCase(name);
	boost::shared_lock<boost::shared_mutex> lock(CharactersMutex);
	for(CharacterMinimalsMap::iterator it = Characters.begin(); it != Characters.end(); ++it)
		if(Desperion::ToLowerCase(it->second->name) == name)
			return it->second;
	return NULL;
}

void World::AddCharacterMinimals(CharacterMinimals* ch)
{
	boost::unique_lock<boost::shared_mutex> lock(CharactersMutex);
	Characters[ch->id] = ch;
}

CharacterMinimals* World::GetCharacterMinimals(int guid)
{
	boost::shared_lock<boost::shared_mutex> lock(CharactersMutex);
	CharacterMinimalsMap::iterator it = Characters.find(guid);
	if(it != Characters.end())
		return it->second;
	return NULL;
}

void World::DeleteCharacterMinimals(int guid)
{
	boost::unique_lock<boost::shared_mutex> lock(CharactersMutex);
	CharacterMinimalsMap::iterator it = Characters.find(guid);
	if(it != Characters.end())
		Characters.erase(it);
}

std::list<CharacterMinimals*> World::GetCharactersByAccount(int guid, bool sort)
{
	std::list<CharacterMinimals*> result;
	{
		boost::shared_lock<boost::shared_mutex> lock(CharactersMutex);
		for(CharacterMinimalsMap::iterator it = Characters.begin(); it != Characters.end(); ++it)
			if(it->second->account == guid)
				result.push_back(it->second);
	}
	if(sort)
	{
		struct sort
		{
			bool operator()(CharacterMinimals* ch1, CharacterMinimals* ch2)
			{ return ch1->lastConnectionDate > ch2->lastConnectionDate; }
		};
		result.sort(sort());
	}
	return result;
}

Item* World::GetItem(int id)
{
	ItemMap::iterator it = Items.find(id);
	if(it != Items.end())
		return it->second;
	return NULL;
}

ItemSet* World::GetItemSet(int16 id)
{
	ItemSetMap::iterator it = ItemSets.find(id);
	if(it != ItemSets.end())
		return it->second;
	return NULL;
}

void World::AddSession(Session* s)
{
	{
		boost::unique_lock<boost::shared_mutex> lock(SessionsMutex);
		Sessions[s->GetData(FLAG_GUID).intValue] = s;
	}
	if(Sessions.size() > m_maxPlayers)
		m_maxPlayers = Sessions.size();
}

Session* World::GetSession(int guid)
{
	boost::shared_lock<boost::shared_mutex> lock(SessionsMutex);
	SessionMap::iterator it = Sessions.find(guid);
	if(it != Sessions.end())
		return it->second;
	return NULL;
}

Session* World::GetSession(std::string pseudo)
{
	pseudo = Desperion::ToLowerCase(pseudo);
	boost::shared_lock<boost::shared_mutex> lock(SessionsMutex);
	for(SessionMap::iterator it = Sessions.begin(); it != Sessions.end(); ++it)
		if(Desperion::ToLowerCase(it->second->GetData(FLAG_PSEUDO).stringValue) == pseudo)
			return it->second;
	return NULL;
}

void World::DeleteSession(int guid)
{
	boost::unique_lock<boost::shared_mutex> lock(SessionsMutex);
	SessionMap::iterator it = Sessions.find(guid);
	if(it != Sessions.end())
		Sessions.erase(it);
}