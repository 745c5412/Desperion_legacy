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

	void Serialize(ByteBuffer& data) const
	{
		int8 b = 0;
		BooleanByteWrapper::SetFlag(b, 0, cantBeAggressed);
		BooleanByteWrapper::SetFlag(b, 1, cantBeChallenged);
		BooleanByteWrapper::SetFlag(b, 2, cantTrade);
		BooleanByteWrapper::SetFlag(b, 3, cantBeAttackedByMutant);
		BooleanByteWrapper::SetFlag(b, 4, cantRun);
		BooleanByteWrapper::SetFlag(b, 5, forceSlowWalk);
		BooleanByteWrapper::SetFlag(b, 6, cantMinimize);
		BooleanByteWrapper::SetFlag(b, 7, cantMove);
		data<<b;
		b = 0;
		BooleanByteWrapper::SetFlag(b, 0, cantAggress);
		BooleanByteWrapper::SetFlag(b, 1, cantChallenge);
		BooleanByteWrapper::SetFlag(b, 2, cantExchange);
		BooleanByteWrapper::SetFlag(b, 3, cantAttack);
		BooleanByteWrapper::SetFlag(b, 4, cantChat);
		BooleanByteWrapper::SetFlag(b, 5, cantBeMerchant);
		BooleanByteWrapper::SetFlag(b, 6, cantUseObject);
		BooleanByteWrapper::SetFlag(b, 7, cantUseTaxCollector);
		data<<b;
		b = 0;
		BooleanByteWrapper::SetFlag(b, 0, cantUseInteractive);
		BooleanByteWrapper::SetFlag(b, 1, cantSpeakToNPC);
		BooleanByteWrapper::SetFlag(b, 2, cantChangeZone);
		BooleanByteWrapper::SetFlag(b, 3, cantAttackMonster);
		BooleanByteWrapper::SetFlag(b, 4, cantWalk8Directions);
		data<<b;
	}

	void Deserialize(ByteBuffer& data)
	{
		int8 b;
		data>>b;
		cantBeAggressed = BooleanByteWrapper::GetFlag(b, 0);
		cantBeChallenged = BooleanByteWrapper::GetFlag(b, 1);
		cantTrade = BooleanByteWrapper::GetFlag(b, 2);
		cantBeAttackedByMutant = BooleanByteWrapper::GetFlag(b, 3);
		cantRun = BooleanByteWrapper::GetFlag(b, 4);
		forceSlowWalk = BooleanByteWrapper::GetFlag(b, 5);
		cantMinimize = BooleanByteWrapper::GetFlag(b, 6);
		cantMove = BooleanByteWrapper::GetFlag(b, 7);
		data>>b;
		cantAggress = BooleanByteWrapper::GetFlag(b, 0);
		cantChallenge = BooleanByteWrapper::GetFlag(b, 1);
		cantExchange = BooleanByteWrapper::GetFlag(b, 2);
		cantAttack = BooleanByteWrapper::GetFlag(b, 3);
		cantChat = BooleanByteWrapper::GetFlag(b, 4);
		cantBeMerchant = BooleanByteWrapper::GetFlag(b, 5);
		cantUseObject = BooleanByteWrapper::GetFlag(b, 6);
		cantUseTaxCollector = BooleanByteWrapper::GetFlag(b, 7);
		data>>b;
		cantUseInteractive = BooleanByteWrapper::GetFlag(b, 0);
		cantSpeakToNPC = BooleanByteWrapper::GetFlag(b, 1);
		cantChangeZone = BooleanByteWrapper::GetFlag(b, 2);
		cantAttackMonster = BooleanByteWrapper::GetFlag(b, 3);
		cantWalk8Directions = BooleanByteWrapper::GetFlag(b, 4);
		data>>b;
	}
};

typedef boost::shared_ptr<ActorRestrictionsInformations> ActorRestrictionsInformationsPtr;

#endif