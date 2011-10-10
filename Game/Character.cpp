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

ByteBuffer Character::SerializeActor() const
{
	ByteBuffer buffer;
	buffer<<uint16(GAME_ROLE_PLAY_CHARACTER_INFORMATIONS)<<int(0); // int(0) => contextualId
	buffer<<m_look.Serialize(const_cast<Character*>(this))<<uint16(ENTITY_DISPOSITION_INFORMATIONS)<<m_currentCell<<m_direction;
	buffer<<m_name<<uint16(HUMAN_INFORMATIONS)<<uint16(0); // todo: HumanWithGuild, uint16(0) = sizeof(followingCharactersLook)
	buffer<<uint8(0)<<uint64(0); // emoteId, emoteTimer
	uint8 r1 = 0;
	Desperion::BooleanByteWrapper::SetFlag(r1, 0, m_restrictions[cantBeAggressed]);
	Desperion::BooleanByteWrapper::SetFlag(r1, 1, m_restrictions[cantBeChallenged]);
	Desperion::BooleanByteWrapper::SetFlag(r1, 2, m_restrictions[cantTrade]);
	Desperion::BooleanByteWrapper::SetFlag(r1, 3, m_restrictions[cantBeAttackedByMutant]);
	Desperion::BooleanByteWrapper::SetFlag(r1, 4, m_restrictions[cantRun]);
	Desperion::BooleanByteWrapper::SetFlag(r1, 5, m_restrictions[forceSlowWalk]);
	Desperion::BooleanByteWrapper::SetFlag(r1, 6, m_restrictions[cantMinimize]);
	Desperion::BooleanByteWrapper::SetFlag(r1, 7, m_restrictions[cantMove]);
	buffer<<r1;
	uint8 r2 = 0;
	Desperion::BooleanByteWrapper::SetFlag(r2, 0, m_restrictions[cantAggress]);
	Desperion::BooleanByteWrapper::SetFlag(r2, 1, m_restrictions[cantChallenge]);
	Desperion::BooleanByteWrapper::SetFlag(r2, 2, m_restrictions[cantExchange]);
	Desperion::BooleanByteWrapper::SetFlag(r2, 3, m_restrictions[cantAttack]);
	Desperion::BooleanByteWrapper::SetFlag(r2, 4, m_restrictions[cantChat]);
	Desperion::BooleanByteWrapper::SetFlag(r2, 5, m_restrictions[cantBeMerchant]);
	Desperion::BooleanByteWrapper::SetFlag(r2, 6, m_restrictions[cantUseObject]);
	Desperion::BooleanByteWrapper::SetFlag(r2, 7, m_restrictions[cantUseTaxCollector]);
	buffer<<r2;
	uint8 r3 = 0;
	Desperion::BooleanByteWrapper::SetFlag(r3, 0, m_restrictions[cantUseInteractive]);
	Desperion::BooleanByteWrapper::SetFlag(r3, 1, m_restrictions[cantSpeakToNPC]);
	Desperion::BooleanByteWrapper::SetFlag(r3, 2, m_restrictions[cantChangeZone]);
	Desperion::BooleanByteWrapper::SetFlag(r3, 3, m_restrictions[cantAttackMonster]);
	Desperion::BooleanByteWrapper::SetFlag(r3, 4, m_restrictions[cantWalk8Directions]);
	buffer<<r3;
	buffer<<m_title<<std::string(""); // "" = titleParams
	buffer<<m_stats.GetAlignmentSide()<<m_stats.GetAlignmentValue()<<m_stats.GetAlignmentGrade();
	buffer<<m_stats.GetDishonor()<<m_stats.GetCharacterPower();
	return buffer;
}

ByteBuffer Character::SerializeStats() const
{
	ByteBuffer buffer;
	buffer<<m_stats.GetXp()<<uint64(0)<<uint64(0); // floor, ceil
	buffer<<m_stats.GetKamas()<<m_stats.GetStatsPoints()<<m_stats.GetSpellsPoints();
	buffer<<m_stats.GetAlignmentSide()<<m_stats.GetAlignmentValue()<<m_stats.GetAlignmentGrade();
	buffer<<m_stats.GetDishonor()<<m_stats.GetCharacterPower()<<m_stats.GetHonor();
	buffer<<uint16(0)<<uint16(0); // floor, ceil
	buffer<<m_stats.IsPvpEnabled();

	buffer<<GetCurrentLife();
	buffer<<GetMaxLife();
	buffer<<m_stats.GetEnergy();
	buffer<<int16(10000); // energyMax
	buffer<<m_stats.GetCurrentAp()<<m_stats.GetCurrentMp();
	
	buffer<<m_stats.initiative<<m_stats.prospecting<<m_stats.actionPoints<<m_stats.movementPoints;
	buffer<<m_stats.strength<<m_stats.vitality<<m_stats.wisdom<<m_stats.chance<<m_stats.agility<<m_stats.intelligence;
	buffer<<m_stats.range<<m_stats.summonableCreaturesBoost<<m_stats.reflect<<m_stats.criticalHit<<int16(50); // criticalHitWeapon
	buffer<<m_stats.criticalMiss<<m_stats.healBonus<<m_stats.allDamagesBonus<<m_stats.weaponDamagesBonusPercent<<m_stats.damagesBonusPercent;
	buffer<<m_stats.trapBonus<<m_stats.trapBonusPercent<<m_stats.permanentDamagePercent<<m_stats.tackleBlock<<m_stats.tackleEvade;
	buffer<<m_stats.PAAttack<<m_stats.PMAttack<<m_stats.pushDamageBonus<<m_stats.criticalDamageBonus<<m_stats.neutralDamageBonus;
	buffer<<m_stats.earthDamageBonus<<m_stats.waterDamageBonus<<m_stats.airDamageBonus<<m_stats.fireDamageBonus;
	buffer<<m_stats.dodgePALostProbability<<m_stats.dodgePMLostProbability<<m_stats.neutralElementResistPercent;
	buffer<<m_stats.earthElementResistPercent<<m_stats.waterElementResistPercent<<m_stats.airElementResistPercent;
	buffer<<m_stats.fireElementResistPercent<<m_stats.neutralElementReduction<<m_stats.earthElementReduction;
	buffer<<m_stats.waterElementReduction<<m_stats.airElementReduction<<m_stats.fireElementReduction;
	buffer<<m_stats.pushDamageReduction<<m_stats.criticalDamageReduction<<m_stats.pvpNeutralElementResistPercent;
	buffer<<m_stats.pvpEarthElementResistPercent<<m_stats.pvpWaterElementResistPercent<<m_stats.pvpAirElementResistPercent;
	buffer<<m_stats.pvpFireElementResistPercent<<m_stats.pvpNeutralElementReduction<<m_stats.pvpEarthElementReduction;
	buffer<<m_stats.pvpWaterElementReduction<<m_stats.pvpAirElementReduction<<m_stats.pvpFireElementReduction;
	buffer<<uint16(0); // spellModifications

	return buffer;
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
	m_guid = fields[0].GetInt32();
	std::string zaaps = fields[1].GetString();
	{
		ByteBuffer buffer = Desperion::DbToBuffer(zaaps);
		uint16 size;
		buffer>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int zaap;
			buffer>>zaap;
			m_zaaps.push_back(zaap);
		}
	}
	m_currentMap = fields[2].GetInt32();
	m_currentCell = fields[3].GetInt16();
	//spells
	m_saveMap = fields[5].GetInt32();
	m_saveCell = fields[6].GetInt16();
	//jobs
	m_mountXp = fields[8].GetInt8();
	//mount
	m_isDead = fields[10].GetBool();
	m_title = fields[11].GetInt16();
	m_isMerchant = fields[12].GetBool();
	std::string emotes = fields[13].GetString();
	{
		ByteBuffer buffer = Desperion::DbToBuffer(emotes);
		uint16 size;
		buffer>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int8 emote;
			buffer>>emote;
			m_emotes.push_back(emote);
		}
	}

	m_level = ch->level;
	m_name = ch->name;
	m_breed = ch->breed;
	m_sex = ch->sex;
	m_account = ch->account;
	m_look = ch->look;
	m_session = session;
	m_context = ROLE_PLAY;
	m_direction = DIRECTION_SOUTH_WEST;
	ch->onlineCharacter = this;
	InitItems();
	m_stats.Init(fields, m_level);
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
		m_items.push_back(it);
	}while(QR->NextRow());
	delete QR;
}