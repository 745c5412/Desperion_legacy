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

#ifndef __GAME_FIGHT_JOIN_MESSAGE__
#define __GAME_FIGHT_JOIN_MESSAGE__

class GameFightJoinMessage : public DofusMessage
{
public:
	bool canBeCancelled;
	bool canSayReady;
	bool isSpectator;
	bool isFightStarted;
	int timeMaxBeforeFightStart;
	int8 fightType;

	uint16 GetOpcode() const
	{ return SMSG_GAME_FIGHT_JOIN; }

	GameFightJoinMessage()
	{
	}

	GameFightJoinMessage(bool canBeCancelled, bool canSayReady, bool isSpectator, bool isFightStarted, int timeMaxBeforeFightStart, int8 fightType) : canBeCancelled(canBeCancelled), canSayReady(canSayReady), isSpectator(isSpectator), isFightStarted(isFightStarted), timeMaxBeforeFightStart(timeMaxBeforeFightStart), fightType(fightType)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		int8 b = 0;
		BooleanByteWrapper::SetFlag(b, 0, canBeCancelled);
		BooleanByteWrapper::SetFlag(b, 1, canSayReady);
		BooleanByteWrapper::SetFlag(b, 2, isSpectator);
		BooleanByteWrapper::SetFlag(b, 3, isFightStarted);
		data<<b<<timeMaxBeforeFightStart<<fightType;
	}

	void Deserialize(ByteBuffer& data)
	{
		int8 b;
		data>>b;
		canBeCancelled = BooleanByteWrapper::GetFlag(b, 0);
		canSayReady = BooleanByteWrapper::GetFlag(b, 1);
		isSpectator = BooleanByteWrapper::GetFlag(b, 2);
		isFightStarted = BooleanByteWrapper::GetFlag(b, 3);
		data>>timeMaxBeforeFightStart>>fightType;
	}
};

#endif