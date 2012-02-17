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

#ifndef __TAX_COLLECTOR_DIALOG_QUESTION_BASIC_MESSAGE__
#define __TAX_COLLECTOR_DIALOG_QUESTION_BASIC_MESSAGE__

class TaxCollectorDialogQuestionBasicMessage : public DofusMessage
{
public:
	BasicGuildInformationsPtr guildInfo;

	uint16 GetOpcode() const
	{ return SMSG_TAX_COLLECTOR_DIALOG_QUESTION_BASIC; }

	TaxCollectorDialogQuestionBasicMessage()
	{
	}

	TaxCollectorDialogQuestionBasicMessage(BasicGuildInformations* guildInfo) : guildInfo(guildInfo)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		guildInfo->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		guildInfo.reset(new BasicGuildInformations);
		guildInfo->Deserialize(data);
	}
};

#endif