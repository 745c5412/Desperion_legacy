#include "StdAfx.h"

ObjectEffectInteger::ObjectEffectInteger(PlayerItemEffectInteger* effect) : ObjectEffect(effect)
{
	m_buffer<<effect->value;
}