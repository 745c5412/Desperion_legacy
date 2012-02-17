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

#ifndef __IDENTIFICATION_FAILED_MESSAGE__
#define __IDENTIFICATION_FAILED_MESSAGE__

enum IdentificationFailureReason
{
	BAD_VERSION = 1,
	WRONG_CREDENTIALS = 2,
	BANNED = 3,
	KICKED = 4,
	IN_MAINTENANCE = 5,
	TOO_MANY_ON_IP = 6,
	TIME_OUT = 7,
	BAD_IPRANGE = 8,
	CREDENTIALS_RESET = 9,
	UNKNOWN_AUTH_ERROR = 99,
	SPARE = 100,
};

class IdentificationFailedMessage : public DofusMessage
{
public:
	int8 reason;

	uint16 GetOpcode() const
	{ return SMSG_IDENTIFICATION_FAILED; }

	IdentificationFailedMessage()
	{
	}

	IdentificationFailedMessage(int8 reason) : reason(reason)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<reason;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>reason;
	}
};

#endif