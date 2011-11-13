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
	int guid;
	bool alreadyConnected;
	std::string pseudo, question;
	uint64 subscriptionEnd;
	uint8 communityId;

	virtual uint16 GetOpcode() const
	{ return SMSG_IDENTIFICATION_SUCCESS; }

	IdentificationSuccessMessage()
	{
	}

	IdentificationSuccessMessage(bool hasRights, bool alreadyConnected, std::string pseudo, int guid, uint8 communityId, std::string question, 
		uint64 subscriptionEnd) : hasRights(hasRights), alreadyConnected(alreadyConnected), pseudo(pseudo), guid(guid), question(question), 
		subscriptionEnd(subscriptionEnd), communityId(communityId)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		uint8 flag = 0;
		Desperion::BooleanByteWrapper::SetFlag(flag, 0, hasRights);
		Desperion::BooleanByteWrapper::SetFlag(flag, 1, alreadyConnected);
		data<<flag<<pseudo<<guid<<communityId<<question<<subscriptionEnd;
	}

	void Deserialize(ByteBuffer& data)
	{
		uint8 flag;
		data>>flag;
		hasRights = Desperion::BooleanByteWrapper::GetFlag(flag, 0);
		alreadyConnected = Desperion::BooleanByteWrapper::GetFlag(flag, 1);
		data>>pseudo>>guid>>communityId>>question>>subscriptionEnd;
	}
};

#endif