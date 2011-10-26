#include "StdAfx.h"

ObjectEffectDice::ObjectEffectDice(PlayerItemEffectDice* effect) : ObjectEffect(effect)
{
	m_buffer<<effect->diceNum<<effect->diceSide<<effect->diceConst;
}