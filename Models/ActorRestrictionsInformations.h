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

#ifndef __ACTOR_RESTRICTIONS_INFORMATIONS__
#define __ACTOR_RESTRICTIONS_INFORMATIONS__

class ActorRestrictionsInformations : public DofusModel
{
public:
	bool cantBeAggressed;
	bool cantBeChallenged;
	bool cantTrade;
	bool cantBeAttackedByMutant;
	bool cantRun;
	bool forceSlowWalk;
	bool cantMinimize;
	bool cantMove;
	bool cantAggress;
	bool cantChallenge;
	bool cantExchange;
	bool cantAttack;
	bool cantChat;
	bool cantBeMerchant;
	bool cantUseObject;
	bool cantUseTaxCollector;
	bool cantUseInteractive;
	bool cantSpeakToNPC;
	bool cantChangeZone;
	bool cantAttackMonster;
	bool cantWalk8Directions;

	uint16 GetProtocol() const
	{ return ACTOR_RESTRICTIONS_INFORMATIONS; }

	ActorRestrictionsInformations()
	{
	}

	ActorRestrictionsInformations(bool cantBeAggressed, bool cantBeChallenged, bool cantTrade, bool cantBeAttackedByMutant, bool cantRun, bool forceSlowWalk, bool cantMinimize, bool cantMove, bool cantAggress, bool cantChallenge, bool cantExchange, bool cantAttack, bool cantChat, bool cantBeMerchant, bool cantUseObject, bool cantUseTaxCollector, bool cantUseInteractive, bool cantSpeakToNPC, bool cantChangeZone, bool cantAttackMonster, bool cantWalk8Directions) : cantBeAggressed(cantBeAggressed), cantBeChallenged(cantBeChallenged), cantTrade(cantTrade), cantBeAttackedByMutant(cantBeAttackedByMutant), cantRun(cantRun), forceSlowWalk(forceSlowWalk), cantMinimize(cantMinimize), cantMove(cantMove), cantAggress(cantAggress), cantChallenge(cantChallenge), cantExchange(cantExchange), cantAttack(cantAttack), cantChat(cantChat), cantBeMerchant(cantBeMerchant), cantUseObject(cantUseObject), cantUseTaxCollector(cantUseTaxCollector), cantUseInteractive(cantUseInteractive), cantSpeakToNPC(cantSpeakToNPC), cantChangeZone(cantChangeZone), cantAttackMonster(cantAttackMonster), cantWalk8Directions(cantWalk8Directions)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		int8 b = 0;
		Desperion::BooleanByteWrapper::SetFlag(b, 0, cantBeAggressed);
		Desperion::BooleanByteWrapper::SetFlag(b, 1, cantBeChallenged);
		Desperion::BooleanByteWrapper::SetFlag(b, 2, cantTrade);
		Desperion::BooleanByteWrapper::SetFlag(b, 3, cantBeAttackedByMutant);
		Desperion::BooleanByteWrapper::SetFlag(b, 4, cantRun);
		Desperion::BooleanByteWrapper::SetFlag(b, 5, forceSlowWalk);
		Desperion::BooleanByteWrapper::SetFlag(b, 6, cantMinimize);
		Desperion::BooleanByteWrapper::SetFlag(b, 7, cantMove);
		data<<b;
		b = 0;
		Desperion::BooleanByteWrapper::SetFlag(b, 0, cantAggress);
		Desperion::BooleanByteWrapper::SetFlag(b, 1, cantChallenge);
		Desperion::BooleanByteWrapper::SetFlag(b, 2, cantExchange);
		Desperion::BooleanByteWrapper::SetFlag(b, 3, cantAttack);
		Desperion::BooleanByteWrapper::SetFlag(b, 4, cantChat);
		Desperion::BooleanByteWrapper::SetFlag(b, 5, cantBeMerchant);
		Desperion::BooleanByteWrapper::SetFlag(b, 6, cantUseObject);
		Desperion::BooleanByteWrapper::SetFlag(b, 7, cantUseTaxCollector);
		data<<b;
		b = 0;
		Desperion::BooleanByteWrapper::SetFlag(b, 0, cantUseInteractive);
		Desperion::BooleanByteWrapper::SetFlag(b, 1, cantSpeakToNPC);
		Desperion::BooleanByteWrapper::SetFlag(b, 2, cantChangeZone);
		Desperion::BooleanByteWrapper::SetFlag(b, 3, cantAttackMonster);
		Desperion::BooleanByteWrapper::SetFlag(b, 4, cantWalk8Directions);
		data<<b;
	}

	void Deserialize(ByteBuffer& data)
	{
		int8 b;
		data>>b;
		cantBeAggressed = Desperion::BooleanByteWrapper::GetFlag(b, 0);
		cantBeChallenged = Desperion::BooleanByteWrapper::GetFlag(b, 1);
		cantTrade = Desperion::BooleanByteWrapper::GetFlag(b, 2);
		cantBeAttackedByMutant = Desperion::BooleanByteWrapper::GetFlag(b, 3);
		cantRun = Desperion::BooleanByteWrapper::GetFlag(b, 4);
		forceSlowWalk = Desperion::BooleanByteWrapper::GetFlag(b, 5);
		cantMinimize = Desperion::BooleanByteWrapper::GetFlag(b, 6);
		cantMove = Desperion::BooleanByteWrapper::GetFlag(b, 7);
		data>>b;
		cantAggress = Desperion::BooleanByteWrapper::GetFlag(b, 0);
		cantChallenge = Desperion::BooleanByteWrapper::GetFlag(b, 1);
		cantExchange = Desperion::BooleanByteWrapper::GetFlag(b, 2);
		cantAttack = Desperion::BooleanByteWrapper::GetFlag(b, 3);
		cantChat = Desperion::BooleanByteWrapper::GetFlag(b, 4);
		cantBeMerchant = Desperion::BooleanByteWrapper::GetFlag(b, 5);
		cantUseObject = Desperion::BooleanByteWrapper::GetFlag(b, 6);
		cantUseTaxCollector = Desperion::BooleanByteWrapper::GetFlag(b, 7);
		data>>b;
		cantUseInteractive = Desperion::BooleanByteWrapper::GetFlag(b, 0);
		cantSpeakToNPC = Desperion::BooleanByteWrapper::GetFlag(b, 1);
		cantChangeZone = Desperion::BooleanByteWrapper::GetFlag(b, 2);
		cantAttackMonster = Desperion::BooleanByteWrapper::GetFlag(b, 3);
		cantWalk8Directions = Desperion::BooleanByteWrapper::GetFlag(b, 4);
		data>>b;
	}
};

typedef boost::shared_ptr<ActorRestrictionsInformations> ActorRestrictionsInformationsPtr;

#endif