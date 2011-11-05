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

PlayerItem* Character::GetItem(int guid)
{
	for(std::list<PlayerItem*>::iterator it = m_items.begin(); it != m_items.end(); ++it)
		if((*it)->GetGuid() == guid)
			return *it;
	return NULL;
}

bool Character::HasEquiped(int16 id)
{
	for(std::list<PlayerItem*>::iterator it = m_items.begin(); it != m_items.end(); ++it)
		if((*it)->GetPos() != INVENTORY_POSITION_NOT_EQUIPED && (*it)->GetItem()->GetId() == id)
			return true;
	return false;
}

PlayerItem* Character::GetItemByPos(uint8 pos)
{
	if(pos == INVENTORY_POSITION_NOT_EQUIPED)
		return NULL;
	for(std::list<PlayerItem*>::iterator it = m_items.begin(); it != m_items.end(); ++it)
		if((*it)->GetPos() == pos)
			return *it;
	return NULL;
}

void Character::UpdateItemSet(int16 set, boost::function<void()> bind)
{
	std::vector<int16> old_items;
	if(set != -1)
		old_items = GetItemsFromSet(set);
	bind();

	if(set != -1)
	{
		std::vector<int16> new_items = GetItemsFromSet(set);
		if(old_items.size() != new_items.size())
		{
			ItemSet* IS = World::Instance().GetItemSet(set);
			if(IS != NULL)
			{
				const std::vector<EffectInstance*>& e1 = IS->GetEffect(old_items.size());
				ItemSet::ApplyEffects(this, e1, false);
				const std::vector<EffectInstance*>& e2 = IS->GetEffect(new_items.size());
				ItemSet::ApplyEffects(this, e2, true);
				m_session->Send(SetUpdateMessage(IS->GetId(), new_items, e2));
			}
		}
	}
}

void Character::DeleteItem(int guid, bool dealloc, bool db)
{
	for(std::list<PlayerItem*>::iterator it = m_items.begin(); it != m_items.end(); ++it)
	{
		if((*it)->GetGuid() == guid)
		{
			if(dealloc)
				delete *it;
			if(db)
				PlayerItem::DeleteFromDB(guid);
			m_items.erase(it);
			return;
		}
	}
}

void Character::AddItem(PlayerItem* item)
{
	m_items.push_back(item);
}

PlayerItem* Character::GetSimilarItem(PlayerItem* i)
{
	for(std::list<PlayerItem*>::iterator it = m_items.begin(); it != m_items.end(); ++it)
	{
		PlayerItem* i2 = *it;
		if(i2->GetItem()->GetId() == i->GetItem()->GetId()
			&& i->GetGuid() != i2->GetGuid() && i2->GetPos() == INVENTORY_POSITION_NOT_EQUIPED
			&& PlayerItem::SameStats(i, i2))
			return i2;
	}
	return NULL;
}

std::vector<int16> Character::GetItemsFromSet(int16 id)
{
	std::vector<int16> items;
	for(std::list<PlayerItem*>::iterator it = m_items.begin(); it != m_items.end(); ++it)
		if((*it)->GetPos() != INVENTORY_POSITION_NOT_EQUIPED && (*it)->GetItem()->GetItemSetId() == id)
			items.push_back((*it)->GetItem()->GetId());
	return items;
}

std::tr1::unordered_map<int16, std::vector<int16> > Character::GetTotalItemSets()
{
	std::tr1::unordered_map<int16, std::vector<int16> > sets;

	for(std::list<PlayerItem*>::iterator it = m_items.begin(); it != m_items.end(); ++it)
	{
		if((*it)->GetPos() != INVENTORY_POSITION_NOT_EQUIPED && (*it)->GetItem()->GetItemSetId() != -1)
			sets[(*it)->GetItem()->GetItemSetId()].push_back((*it)->GetItem()->GetId());
	}
	return sets;
}

void Character::MoveItem(PlayerItem* item, uint8 pos, bool create)
{
	PlayerItem* item2;
	if(pos == INVENTORY_POSITION_NOT_EQUIPED && (item2 = GetSimilarItem(item)) != NULL)
	{
		item->SetPos(INVENTORY_POSITION_NOT_EQUIPED);
		item2->SetQuantity(item2->GetQuantity() + item->GetQuantity());
		m_session->Send(ObjectQuantityMessage(item2->GetGuid(), item2->GetQuantity()));

		if(!create)
			m_session->Send(ObjectDeletedMessage(item->GetGuid()));
		DeleteItem(item->GetGuid(), true, true);
	}
	else
	{
		if(item->GetQuantity() > 1 && !create)
		{
			PlayerItem* newItem = new PlayerItem;
			newItem->Init(PlayerItem::GetNextItemGuid(), item->GetItem(), 1, INVENTORY_POSITION_NOT_EQUIPED, item->GetEffects(), this);
			item->SetQuantity(item->GetQuantity() - 1);
			AddItem(newItem);
			newItem->SetPos(pos);
			PlayerItem::InsertIntoDB(newItem);

			m_session->Send(ObjectAddedMessage(ObjectItem(newItem)));
			m_session->Send(ObjectQuantityMessage(item->GetGuid(), item->GetQuantity()));
		}
		else
		{
			if(!create)
			{
				item->SetPos(pos);
				m_session->Send(ObjectMovementMessage(item->GetGuid(), item->GetPos()));
			}
			else
				m_session->Send(ObjectAddedMessage(ObjectItem(item)));
		}
	}
}

void Character::MoveItemFromMap(PlayerItem* item)
{
	PlayerItem* item2;
	if((item2 = GetSimilarItem(item)) != NULL)
	{
		item2->SetQuantity(item2->GetQuantity() + item->GetQuantity());
		PlayerItem::DeleteFromDB(item->GetGuid());
		delete item;

		m_session->Send(ObjectQuantityMessage(item2->GetGuid(), item2->GetQuantity()));
	}
	else
	{
		item->SetOwner(this);
		AddItem(item);

		m_session->Send(ObjectAddedMessage(ObjectItem(item)));
		item->Save();
	}
}

void Character::Save()
{
	for(std::list<PlayerItem*>::iterator it = m_items.begin(); it != m_items.end(); ++it)
		(*it)->Save();

	std::ostringstream zaaps;
	for(size_t a = 0; a < m_zaaps.size(); ++a)
	{
		if(a != 0)
			zaaps<<",";
		zaaps<<m_zaaps.at(a);
	}

	std::ostringstream emotes;
	for(size_t a = 0; a < m_emotes.size(); ++a)
	{
		if(a != 0)
			emotes<<",";
		emotes<<uint16(m_emotes.at(a));
	}
	Desperion::sDatabase->Execute("UPDATE characters SET zaaps='%s', currentMap=%u, currentCell=%u, spells='%s', saveMap=%u, \
								  saveCell=%u, jobs='%s', mountXp=%u, mountId=%d, isDead=%u, title=%u, isMerchant=%u, emotes='%s' \
								  WHERE guid=%u LIMIT 1;", zaaps.str().c_str(), m_map->GetId(), m_cell, "", m_saveMap, m_saveCell,
								  "", m_mountXp, -1, 0, m_title, 0, emotes.str().c_str(), m_guid);
	Desperion::sDatabase->Execute("UPDATE character_minimals SET level=%u, name='%s', entityLook='%s', breed=%u, sex=%u \
								  WHERE id=%u LIMIT 1;", m_level, m_name.c_str(), Desperion::BufferToDb(m_look.Serialize(-1)).c_str(), m_breed, 
								  m_sex ? 1 : 0, m_guid);
	// TODO: update stats
}

Character::~Character()
{
	CharacterMinimals* ch = World::Instance().GetCharacterMinimals(m_guid);
	if(ch != NULL)
		ch->onlineCharacter = NULL;
	for(std::list<PlayerItem*>::iterator it = m_items.begin(); it != m_items.end(); ++it)
		delete *it;
	m_items.clear();
}

void Character::Init(Field* fields, CharacterMinimals* ch, Session* session)
{
	int mapId = fields[2].GetInt32();
	Map* map = World::Instance().GetMap(mapId);
	if(map == NULL)
	{
		std::ostringstream str;
		str<<"Map "<<mapId<<" doesn't exist!";
		throw ServerError(str.str().c_str());
	}
	DisplayableEntity::Init(fields[0].GetInt32(), ch->look, fields[3].GetInt16(), World::Instance().GetMap(fields[2].GetInt32()), 
		DIRECTION_SOUTH_WEST);
	NamedEntity::Init(ch->name);
	HumanEntity::Init(0, 0, fields[11].GetInt16(), "");

	Desperion::FastSplit<','>(m_zaaps, std::string(fields[1].GetString()), Desperion::SplitInt, true);
	//spells
	m_saveMap = fields[5].GetInt32();
	m_saveCell = fields[6].GetInt16();
	//jobs
	m_mountXp = fields[8].GetInt8();
	//mount
	m_isDead = fields[10].GetBool();
	m_isMerchant = fields[12].GetBool();
	Desperion::FastSplit<','>(m_emotes, std::string(fields[13].GetString()), Desperion::SplitInt, true);

	m_level = ch->level;
	m_breed = ch->breed;
	m_sex = ch->sex;
	m_account = ch->account;
	m_session = session;
	m_context = ROLE_PLAY;
	m_nextCell = -1;
	m_nextDirection = -1;
	ch->onlineCharacter = this;
	InitItems();
	m_stats.Init(fields, m_level);
	ApplyEffect(&StatsRow::base, 125, fields[25].GetInt16(), true);
	ApplyEffect(&StatsRow::base, 124, fields[26].GetInt16(), true);
	ApplyEffect(&StatsRow::base, 118, fields[27].GetInt16(), true);
	ApplyEffect(&StatsRow::base, 126, fields[28].GetInt16(), true);
	ApplyEffect(&StatsRow::base, 123, fields[29].GetInt16(), true);
	ApplyEffect(&StatsRow::base, 119, fields[30].GetInt16(), true);
	
	// TODO: timer de regen
}

void Character::InitItems()
{
	QueryResult* QR = Desperion::sDatabase->Query("SELECT * FROM character_items WHERE owner=%u;", m_guid);
	if(!QR)
		return;
	do
	{
		Field* fields = QR->Fetch();
		PlayerItem* it = new PlayerItem;
		it->Init(fields);
		PlayerItemEffectDate* obviTime = (PlayerItemEffectDate*)it->GetEffect(808),
			* exchangeTime = (PlayerItemEffectDate*)it->GetEffect(983);

		time_t t = time(NULL);
		if(obviTime != NULL)
		{
			struct tm* tm = localtime(&t);
			tm->tm_year = obviTime->year;
			tm->tm_mon = obviTime->month;
			tm->tm_mday = obviTime->day;
			tm->tm_hour = obviTime->hour;
			tm->tm_min = obviTime->minute;
			if(t - mktime(tm) > 36 * 60 * 60)
			{
				uint8 state = ((PlayerItemEffectInteger*)it->GetEffect(971))->value;
				switch(state)
				{
				case 1:
				case 2:
					it->DeleteEffect(808);
					it->DeleteEffect(971);

					/* on actualise le repas pour éviter les réactions en chaîne, et pour que le
					  joueur ne puisse pas le renourrir tout de suite (enfin, ça le rendra obèse si il est rassasié) */

					struct tm* tm2 = localtime(&t);
					it->AddEffect(new PlayerItemEffectDate(808, tm2->tm_year, tm2->tm_mon, tm2->tm_mday, tm2->tm_hour,
						tm2->tm_min));
					it->AddEffect(new PlayerItemEffectInteger(971, state - 1));
					break;
				}
			}
		}
		if(exchangeTime != NULL)
		{
			struct tm* tm = localtime(&t);
			tm->tm_year = exchangeTime->year;
			tm->tm_mon = exchangeTime->month;
			tm->tm_mday = exchangeTime->day;
			tm->tm_hour = exchangeTime->hour;
			tm->tm_min = exchangeTime->minute;
			if(t - mktime(tm) > 0)
				it->DeleteEffect(983);
		}

		m_items.push_back(it);
	}while(QR->NextRow());
	delete QR;
}

bool Character::ApplyEffect(double StatsRow::*stat, int id, int val, bool add)
{
	EffectInstanceInteger e;
	e.value = val;
	e.effectId = id;
	return ApplyEffect(stat, e, add);
}

bool Character::ApplyEffect(double StatsRow::*stat, EffectInstanceInteger& e, bool add)
{
	// TODO: stats speciales telles que "Debloque le titre X", "Change l'apparence"... etc

	double v;
	if(add)
		v = e.value;
	else
		v = -e.value;
	switch(e.effectId)
	{
	case 1076: // +resistance % all (bond par exemple, mais je doute que cette stat soit utilisee dans les effets d'items)
		m_stats.neutralElementResistPercent.*stat += v;
		m_stats.fireElementResistPercent.*stat += v;
		m_stats.waterElementResistPercent.*stat += v;
		m_stats.airElementResistPercent.*stat += v;
		m_stats.earthElementResistPercent.*stat += v;
		break;
	case 1077: // -resistance % all
		m_stats.neutralElementResistPercent.*stat -= v;
		m_stats.fireElementResistPercent.*stat -= v;
		m_stats.waterElementResistPercent.*stat -= v;
		m_stats.airElementResistPercent.*stat -= v;
		m_stats.earthElementResistPercent.*stat -= v;
		break;
	case 124:
		m_stats.wisdom.*stat += v;
		m_stats.dodgePALostProbability.*stat += v/10;
		m_stats.dodgePMLostProbability.*stat += v/10;
		m_stats.PAAttack.*stat += v/10;
		m_stats.PMAttack.*stat += v/10;
		break;
	case 156:
		m_stats.wisdom.*stat -= v;
		m_stats.dodgePALostProbability.*stat -= v/10;
		m_stats.dodgePMLostProbability.*stat -= v/10;
		m_stats.PAAttack.*stat -= v/10;
		m_stats.PMAttack.*stat -= v/10;
		break;
	case 126:
		m_stats.intelligence.*stat += v;
		m_stats.healBonus.*stat += v/10;
		m_stats.initiative.*stat += v;
		break;
	case 155:
		m_stats.intelligence.*stat -= v;
		m_stats.healBonus.*stat -= v/10;
		m_stats.initiative.*stat -= v;
		break;
	case 119:
		m_stats.agility.*stat += v;
		m_stats.tackleBlock.*stat += v/10;
		m_stats.tackleEvade.*stat += v/10;
		m_stats.initiative.*stat += v;
		break;
	case 154:
		m_stats.agility.*stat -= v;
		m_stats.tackleBlock.*stat -= v/10;
		m_stats.tackleEvade.*stat -= v/10;
		m_stats.initiative.*stat -= v;
		break;
	case 123:
		m_stats.chance.*stat += v;
		m_stats.prospecting.*stat += v/10;
		m_stats.initiative.*stat += v;
		break;
	case 152:
		m_stats.chance.*stat -= v;
		m_stats.prospecting.*stat -= v/10;
		m_stats.initiative.*stat -= v;
		break;
	case 125:
		m_stats.vitality.*stat += v;
		break;
	case 153:
		m_stats.vitality.*stat -= v;
		break;
	case 118:
		m_stats.strength.*stat += v;
		m_stats.initiative.*stat += v;
		break;
	case 157:
		m_stats.strength.*stat -= v;
		m_stats.initiative.*stat -= v;
		break;
	case 430:
		m_stats.neutralDamageBonus.*stat += v;
		break;
	case 431:
		m_stats.neutralDamageBonus.*stat -= v;
		break;
	case 428:
		m_stats.airDamageBonus.*stat += v;
		break;
	case 429:
		m_stats.airDamageBonus.*stat -= v;
		break;
	case 426:
		m_stats.waterDamageBonus.*stat += v;
		break;
	case 427:
		m_stats.waterDamageBonus.*stat -= v;
		break;
	case 424:
		m_stats.fireDamageBonus.*stat += v;
		break;
	case 425:
		m_stats.fireDamageBonus.*stat -= v;
		break;
	case 422:
		m_stats.earthDamageBonus.*stat += v;
		break;
	case 423:
		m_stats.earthDamageBonus.*stat -= v;
		break;
	case 420:
		m_stats.criticalDamageReduction.*stat += v;
		break;
	case 421:
		m_stats.criticalDamageReduction.*stat -= v;
		break;
	case 418:
		m_stats.criticalDamageBonus.*stat += v;
		break;
	case 419:
		m_stats.criticalDamageBonus.*stat -= v;
		break;
	case 416:
		m_stats.pushDamageReduction.*stat += v;
		break;
	case 417:
		m_stats.pushDamageReduction.*stat -= v;
		break;
	case 414:
		m_stats.pushDamageBonus.*stat += v;
		break;
	case 415:
		m_stats.pushDamageBonus.*stat -= v;
		break;
	case 412:
		m_stats.PMAttack.*stat += v;
		break;
	case 413:
		m_stats.PMAttack.*stat -= v;
		break;
	case 410:
		m_stats.PAAttack.*stat += v;
		break;
	case 411:
		m_stats.PAAttack.*stat -= v;
		break;
	case 753:
		m_stats.tackleBlock.*stat += v;
		break;
	case 755:
		m_stats.tackleBlock.*stat -= v;
		break;
	case 752:
		m_stats.tackleEvade.*stat += v;
		break;
	case 754:
		m_stats.tackleEvade.*stat -= v;
		break;
	case 225:
		m_stats.trapBonus.*stat += v;
		break;
	case 226:
		m_stats.trapBonusPercent.*stat += v;
		break;
	case 264: // bizarrement, il n'y a que les effets positifs pour les pvpElementReduction
		m_stats.pvpNeutralElementReduction.*stat += v;
		break;
	case 262:
		m_stats.pvpAirElementReduction.*stat += v;
		break;
	case 261:
		m_stats.pvpWaterElementReduction.*stat += v;
		break;
	case 263:
		m_stats.pvpFireElementReduction.*stat += v;
		break;
	case 260:
		m_stats.pvpEarthElementReduction.*stat += v;
		break;
	case 254:
		m_stats.pvpNeutralElementResistPercent.*stat += v;
		break;
	case 252:
		m_stats.pvpAirElementResistPercent.*stat += v;
		break;
	case 251:
		m_stats.pvpWaterElementResistPercent.*stat += v;
		break;
	case 253:
		m_stats.pvpFireElementResistPercent.*stat += v;
		break;
	case 250:
		m_stats.pvpEarthElementResistPercent.*stat += v;
		break;
	case 259:
		m_stats.pvpNeutralElementResistPercent.*stat -= v;
		break;
	case 257:
		m_stats.pvpAirElementResistPercent.*stat -= v;
		break;
	case 256:
		m_stats.pvpWaterElementResistPercent.*stat -= v;
		break;
	case 258:
		m_stats.pvpFireElementResistPercent.*stat -= v;
		break;
	case 255:
		m_stats.pvpEarthElementResistPercent.*stat -= v;
		break;
	case 244:
		m_stats.neutralElementReduction.*stat += v;
		break;
	case 242:
		m_stats.airElementReduction.*stat += v;
		break;
	case 241:
		m_stats.waterElementReduction.*stat += v;
		break;
	case 243:
		m_stats.fireElementReduction.*stat += v;
		break;
	case 240:
		m_stats.earthElementReduction.*stat += v;
		break;
	case 249:
		m_stats.neutralElementReduction.*stat -= v;
		break;
	case 247:
		m_stats.airElementReduction.*stat -= v;
		break;
	case 246:
		m_stats.waterElementReduction.*stat -= v;
		break;
	case 248:
		m_stats.fireElementReduction.*stat -= v;
		break;
	case 245:
		m_stats.earthElementReduction.*stat -= v;
		break;
	case 220:
		m_stats.reflect.*stat += v;
		break;
	case 178:
		m_stats.healBonus.*stat += v;
		break;
	case 179:
		m_stats.healBonus.*stat -= v;
		break;
	case 176:
		m_stats.prospecting.*stat += v;
		break;
	case 177:
		m_stats.prospecting.*stat -= v;
		break;
	case 174:
		m_stats.initiative.*stat += v;
		break;
	case 175:
		m_stats.initiative.*stat -= v;
		break;
	case 122:
		m_stats.criticalMiss.*stat += v;
		break;
	case 214:
		m_stats.neutralElementResistPercent.*stat += v;
		break;
	case 212:
		m_stats.airElementResistPercent.*stat += v;
		break;
	case 211:
		m_stats.waterElementResistPercent.*stat += v;
		break;
	case 213:
		m_stats.fireElementResistPercent.*stat += v;
		break;
	case 210:
		m_stats.earthElementResistPercent.*stat += v;
		break;
	case 219:
		m_stats.neutralElementResistPercent.*stat -= v;
		break;
	case 217:
		m_stats.airElementResistPercent.*stat -= v;
		break;
	case 216:
		m_stats.waterElementResistPercent.*stat -= v;
		break;
	case 218:
		m_stats.fireElementResistPercent.*stat -= v;
		break;
	case 215:
		m_stats.earthElementResistPercent.*stat -= v;
		break;
	case 161:
		m_stats.dodgePMLostProbability.*stat += v;
		break;
	case 163:
		m_stats.dodgePMLostProbability.*stat -= v;
		break;
	case 160:
		m_stats.dodgePALostProbability.*stat += v;
		break;
	case 162:
		m_stats.dodgePALostProbability.*stat -= v;
		break;
	case 182:
		m_stats.summonableCreaturesBoost.*stat += v;
		break;
	case 128:
		m_stats.movementPoints.*stat += v;
		break;
	case 127:
		m_stats.movementPoints.*stat -= v;
		break;
	case 184: // +reduc physique (neutre et terre) --> obsolete mais je met quand meme, on sait jamais :)
		m_stats.neutralElementReduction.*stat += v;
		m_stats.earthElementReduction.*stat += v;
		break;
	case 173: // -reduc physique
		m_stats.neutralElementReduction.*stat -= v;
		m_stats.earthElementReduction.*stat -=v;
		break;
	case 183: // +reduc magique (air, eau et feu) --> idem
		m_stats.waterElementReduction.*stat += v;
		m_stats.fireElementReduction.*stat += v;
		m_stats.airElementReduction.*stat += v;
		break;
	case 172: // -reduc magique
		m_stats.waterElementReduction.*stat -= v;
		m_stats.fireElementReduction.*stat -=v;
		m_stats.airElementReduction.*stat -= v;
		break;
	case 117:
		m_stats.range.*stat += v;
		break;
	case 116:
		m_stats.range.*stat -= v;
		break;
	case 115:
		m_stats.criticalHit.*stat += v;
		break;
	case 171:
		m_stats.criticalHit.*stat -= v;
		break;
	case 114: // multiplie les dommages par X, obsolete mais bon, comme d'hab
	case 138:
		m_stats.damagesBonusPercent.*stat += v;
		break;
	case 186:
		m_stats.damagesBonusPercent.*stat -= v;
		break;
	case 112: // +dom normaux (sur les items "post-frigost"); y'a plusieurs valeurs dans le fichier des Effects, donc je suis pas sur
		m_stats.allDamagesBonus.*stat += v;
		break;
	case 145: // -dom normaux
		m_stats.allDamagesBonus.*stat -= v;
		break;
	case 111:
		m_stats.actionPoints.*stat += v;
		break;
	case 168:
		m_stats.actionPoints.*stat -= v;
		break;
	default:
		return false;
	}
	return true;
}