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

#ifndef __EXCHANGE_STARTED_WITH_PODS_MESSAGE__
#define __EXCHANGE_STARTED_WITH_PODS_MESSAGE__

class ExchangeStartedWithPodsMessage : public ExchangeStartedMessage
{
public:
	int firstCharacterId;
	int firstCharacterCurrentWeight;
	int firstCharacterMaxWeight;
	int secondCharacterId;
	int secondCharacterCurrentWeight;
	int secondCharacterMaxWeight;

	uint16 GetOpcode() const
	{ return SMSG_EXCHANGE_STARTED_WITH_PODS; }

	ExchangeStartedWithPodsMessage()
	{
	}

	ExchangeStartedWithPodsMessage(int8 exchangeType, int firstCharacterId, int firstCharacterCurrentWeight, int firstCharacterMaxWeight, int secondCharacterId, int secondCharacterCurrentWeight, int secondCharacterMaxWeight) : ExchangeStartedMessage(exchangeType), firstCharacterId(firstCharacterId), firstCharacterCurrentWeight(firstCharacterCurrentWeight), firstCharacterMaxWeight(firstCharacterMaxWeight), secondCharacterId(secondCharacterId), secondCharacterCurrentWeight(secondCharacterCurrentWeight), secondCharacterMaxWeight(secondCharacterMaxWeight)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		ExchangeStartedMessage::Serialize(data);
		data<<firstCharacterId<<firstCharacterCurrentWeight<<firstCharacterMaxWeight<<secondCharacterId<<secondCharacterCurrentWeight<<secondCharacterMaxWeight;
	}

	void Deserialize(ByteBuffer& data)
	{
		ExchangeStartedMessage::Deserialize(data);
		data>>firstCharacterId>>firstCharacterCurrentWeight>>firstCharacterMaxWeight>>secondCharacterId>>secondCharacterCurrentWeight>>secondCharacterMaxWeight;
	}
};

#endif