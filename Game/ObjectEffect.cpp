#include "StdAfx.h"

ObjectEffect::ObjectEffect(PlayerItemEffect* effect)
{
	m_buffer<<effect->actionId;
}