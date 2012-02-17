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

#ifndef __TAX_COLLECTOR_DIALOG_QUESTION_EXTENDED_MESSAGE__
#define __TAX_COLLECTOR_DIALOG_QUESTION_EXTENDED_MESSAGE__

class TaxCollectorDialogQuestionExtendedMessage : public TaxCollectorDialogQuestionBasicMessage
{
public:
	int16 maxPods;
	int16 prospecting;
	int16 wisdom;
	int8 taxCollectorsCount;
	int taxCollectorAttack;
	int kamas;
	int64 experience;
	int pods;
	int itemsValue;

	uint16 GetOpcode() const
	{ return SMSG_TAX_COLLECTOR_DIALOG_QUESTION_EXTENDED; }

	TaxCollectorDialogQuestionExtendedMessage()
	{
	}

	TaxCollectorDialogQuestionExtendedMessage(BasicGuildInformations* guildInfo, int16 maxPods, int16 prospecting, int16 wisdom, int8 taxCollectorsCount, int taxCollectorAttack, int kamas, int64 experience, int pods, int itemsValue) : TaxCollectorDialogQuestionBasicMessage(guildInfo), maxPods(maxPods), prospecting(prospecting), wisdom(wisdom), taxCollectorsCount(taxCollectorsCount), taxCollectorAttack(taxCollectorAttack), kamas(kamas), experience(experience), pods(pods), itemsValue(itemsValue)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		TaxCollectorDialogQuestionBasicMessage::Serialize(data);
		data<<maxPods<<prospecting<<wisdom<<taxCollectorsCount<<taxCollectorAttack<<kamas<<experience<<pods<<itemsValue;
	}

	void Deserialize(ByteBuffer& data)
	{
		TaxCollectorDialogQuestionBasicMessage::Deserialize(data);
		data>>maxPods>>prospecting>>wisdom>>taxCollectorsCount>>taxCollectorAttack>>kamas>>experience>>pods>>itemsValue;
	}
};

#endif