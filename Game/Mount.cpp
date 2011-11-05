#include "StdAfx.h"

void Mount::Init(Field* fields)
{
	m_id = fields[0].GetInt32();
	m_model = fields[1].GetInt32();
	m_name = fields[2].GetString();
	m_sex = fields[3].GetBool();
}

Mount::~Mount()
{
	for(std::list<PlayerItem*>::iterator it = m_items.begin(); it != m_items.end(); ++it)
		delete *it;
}