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