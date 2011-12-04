#include "StdAfx.h"

void Subarea::Init(Field* fields)
{
	m_id = fields[0].GetInt16();
	m_areaId = fields[1].GetInt32();
	Desperion::FastSplit<';'>(m_spawns, std::string(fields[3].GetString()), S, true);
}