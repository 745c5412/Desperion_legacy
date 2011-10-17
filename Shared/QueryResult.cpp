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

QueryResult::QueryResult(MYSQL_RES *res, uint32 fields, uint32 rows) : m_result(res), m_fieldCount(fields), m_rowCount(rows)
{
	m_currentRow = new Field[fields];
}

QueryResult::~QueryResult()
{
	mysql_free_result(m_result);
	delete [] m_currentRow;
}

bool QueryResult::NextRow()
{
	MYSQL_ROW row = mysql_fetch_row(m_result);
	if(row == NULL)
		return false;

	for(uint32 i = 0; i < m_fieldCount; ++i)
		m_currentRow[i].SetValue(row[i]);

	return true;
}