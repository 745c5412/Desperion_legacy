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

#ifndef __CHARACTER_REPORT_MESSAGE__
#define __CHARACTER_REPORT_MESSAGE__

class CharacterReportMessage : public DofusMessage
{
public:
	uint32 reportedId;
	int8 reason;

	uint16 GetOpcode() const
	{ return CMSG_CHARACTER_REPORT; }

	CharacterReportMessage()
	{
	}

	CharacterReportMessage(uint32 reportedId, int8 reason) : reportedId(reportedId), reason(reason)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<reportedId<<reason;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>reportedId>>reason;
	}
};

#endif