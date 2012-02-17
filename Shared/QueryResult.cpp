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

// J'aurai pu faire plus propre avec le polymorphisme, mais flemme

QueryResult::QueryResult(MYSQL_RES* res, uint32 fields, uint32 rows) : m_mResult(res), m_pResult(NULL), m_fieldCount(fields),
	m_rowCount(rows), m_pRecord(0)
{
	m_currentRow = new Field[fields];
}

QueryResult::QueryResult(PGresult* res, uint32 fields, uint32 rows) : m_mResult(NULL), m_pResult(res), m_fieldCount(fields),
	m_rowCount(rows), m_pRecord(0)
{
	m_currentRow = new Field[fields];
}

QueryResult::~QueryResult()
{
	if(m_mResult != NULL)
		mysql_free_result(m_mResult);
	else if(m_pResult != NULL)
		PQclear(m_pResult);
	delete[] m_currentRow;
}

bool QueryResult::NextRow()
{
	if(m_mResult != NULL)
	{
		MYSQL_ROW row = mysql_fetch_row(m_mResult);
		if(row == NULL)
			return false;
		for(uint32 a = 0; a < m_fieldCount; ++a)
			m_currentRow[a].SetValue(row[a]);
	}
	else if(m_pResult != NULL)
	{
		if(m_pRecord == m_rowCount)
			return false;
		for(uint32 a = 0; a < m_fieldCount; ++a)
			m_currentRow[a].SetValue(PQgetvalue(m_pResult, m_pRecord, a));
		++m_pRecord;
	}
	return true;
}