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

ActorRestrictionsInformations::ActorRestrictionsInformations(HumanEntity* ent) : r1(0), r2(0), r3(0)
{
	Desperion::BooleanByteWrapper::SetFlag(r1, 0, ent->GetRestriction(cantBeAggressed));
	Desperion::BooleanByteWrapper::SetFlag(r1, 1, ent->GetRestriction(cantBeChallenged));
	Desperion::BooleanByteWrapper::SetFlag(r1, 2, ent->GetRestriction(cantTrade));
	Desperion::BooleanByteWrapper::SetFlag(r1, 3, ent->GetRestriction(cantBeAttackedByMutant));
	Desperion::BooleanByteWrapper::SetFlag(r1, 4, ent->GetRestriction(cantRun));
	Desperion::BooleanByteWrapper::SetFlag(r1, 5, ent->GetRestriction(forceSlowWalk));
	Desperion::BooleanByteWrapper::SetFlag(r1, 6, ent->GetRestriction(cantMinimize));
	Desperion::BooleanByteWrapper::SetFlag(r1, 7, ent->GetRestriction(cantMove));

	Desperion::BooleanByteWrapper::SetFlag(r2, 0, ent->GetRestriction(cantAggress));
	Desperion::BooleanByteWrapper::SetFlag(r2, 1, ent->GetRestriction(cantChallenge));
	Desperion::BooleanByteWrapper::SetFlag(r2, 2, ent->GetRestriction(cantExchange));
	Desperion::BooleanByteWrapper::SetFlag(r2, 3, ent->GetRestriction(cantAttack));
	Desperion::BooleanByteWrapper::SetFlag(r2, 4, ent->GetRestriction(cantChat));
	Desperion::BooleanByteWrapper::SetFlag(r2, 5, ent->GetRestriction(cantBeMerchant));
	Desperion::BooleanByteWrapper::SetFlag(r2, 6, ent->GetRestriction(cantUseObject));
	Desperion::BooleanByteWrapper::SetFlag(r2, 7, ent->GetRestriction(cantUseTaxCollector));

	Desperion::BooleanByteWrapper::SetFlag(r3, 0, ent->GetRestriction(cantUseInteractive));
	Desperion::BooleanByteWrapper::SetFlag(r3, 1, ent->GetRestriction(cantSpeakToNPC));
	Desperion::BooleanByteWrapper::SetFlag(r3, 2, ent->GetRestriction(cantChangeZone));
	Desperion::BooleanByteWrapper::SetFlag(r3, 3, ent->GetRestriction(cantAttackMonster));
	Desperion::BooleanByteWrapper::SetFlag(r3, 4, ent->GetRestriction(cantWalk8Directions));
}