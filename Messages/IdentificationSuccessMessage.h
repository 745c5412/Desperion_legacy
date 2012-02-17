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

#ifndef __IDENTIFICATION_SUCCESS_MESSAGE__
#define __IDENTIFICATION_SUCCESS_MESSAGE__

class IdentificationSuccessMessage : public DofusMessage
{
public:
	bool hasRights;
	bool wasAlreadyConnected;
	std::string login;
	std::string nickname;
	int accountId;
	int8 communityId;
	std::string secretQuestion;
	int64 subscriptionEndDate;

	uint16 GetOpcode() const
	{ return SMSG_IDENTIFICATION_SUCCESS; }

	IdentificationSuccessMessage()
	{
	}

	IdentificationSuccessMessage(bool hasRights, bool wasAlreadyConnected, std::string login, std::string nickname, int accountId, int8 communityId, std::string secretQuestion, int64 subscriptionEndDate) : hasRights(hasRights), wasAlreadyConnected(wasAlreadyConnected), login(login), nickname(nickname), accountId(accountId), communityId(communityId), secretQuestion(secretQuestion), subscriptionEndDate(subscriptionEndDate)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		int8 b = 0;
		BooleanByteWrapper::SetFlag(b, 0, hasRights);
		BooleanByteWrapper::SetFlag(b, 1, wasAlreadyConnected);
		data<<b<<login<<nickname<<accountId<<communityId<<secretQuestion<<subscriptionEndDate;
	}

	void Deserialize(ByteBuffer& data)
	{
		int8 b;
		data>>b;
		hasRights = BooleanByteWrapper::GetFlag(b, 0);
		wasAlreadyConnected = BooleanByteWrapper::GetFlag(b, 1);
		data>>login>>nickname>>accountId>>communityId>>secretQuestion>>subscriptionEndDate;
	}
};

#endif