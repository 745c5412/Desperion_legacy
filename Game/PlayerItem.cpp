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

Mutex PlayerItem::m_guidLock;

void PlayerItem::Init(Field* fields)
{
	m_guid = fields[0].GetInt32();
	m_item = World::Instance().GetItem(fields[1].GetInt32());
	m_quantity = fields[2].GetInt32();
	m_pos = fields[3].GetInt32();
	std::string stats = fields[4].GetString();
}

void PlayerItem::Save()
{
}

void PlayerItem::SetPos(int pos)
{
}

int PlayerItem::GetNextItemGuid()
{
	int guid = 1;
	m_guidLock.lock();
	QueryResult* QR = Desperion::sDatabase->Query("SELECT guid FROM character_items ORDER BY guid DESC;");
	if(QR)
		guid = (QR->Fetch()[0].GetInt32()) + 1;
	delete QR;
	m_guidLock.unlock();
	return guid;
}

void PlayerItem::InsertIntoDB(PlayerItem* item)
{
}

void PlayerItem::DeleteFromDB(int guid)
{
	Desperion::sDatabase->Execute("DELETE FROM character_items WHERE guid=%u LIMIT 1;", guid);
}