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

#ifndef __IDENTIFICATION_SUCCESS_WITH_LOGIN_TOKEN_MESSAGE__
#define __IDENTIFICATION_SUCCESS_WITH_LOGIN_TOKEN_MESSAGE__

class IdentificationSuccessWithLoginTokenMessage : public IdentificationSuccessMessage
{
public:
	std::string loginToken;

	uint16 GetOpcode() const
	{ return SMSG_IDENTIFICATION_SUCCESS_WITH_LOGIN_TOKEN; }

	IdentificationSuccessWithLoginTokenMessage()
	{
	}

	IdentificationSuccessWithLoginTokenMessage(bool hasRights, bool wasAlreadyConnected, std::string login, std::string nickname, int accountId, int8 communityId, std::string secretQuestion, int64 subscriptionEndDate, std::string loginToken) : IdentificationSuccessMessage(hasRights, wasAlreadyConnected, login, nickname, accountId, communityId, secretQuestion, subscriptionEndDate), loginToken(loginToken)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		IdentificationSuccessMessage::Serialize(data);
		data<<loginToken;
	}

	void Deserialize(ByteBuffer& data)
	{
		IdentificationSuccessMessage::Deserialize(data);
		data>>loginToken;
	}
};

#endif