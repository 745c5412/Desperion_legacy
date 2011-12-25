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

#ifndef __STARTUP_ACTION_FINISHED_MESSAGE__
#define __STARTUP_ACTION_FINISHED_MESSAGE__

class StartupActionFinishedMessage : public DofusMessage
{
public:
	bool success;
	bool automaticAction;
	int actionId;

	uint16 GetOpcode() const
	{ return SMSG_STARTUP_ACTION_FINISHED; }

	StartupActionFinishedMessage()
	{
	}

	StartupActionFinishedMessage(bool success, bool automaticAction, int actionId) : success(success), automaticAction(automaticAction), actionId(actionId)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		int8 b = 0;
		Desperion::BooleanByteWrapper::SetFlag(b, 0, success);
		Desperion::BooleanByteWrapper::SetFlag(b, 1, automaticAction);
		data<<b<<actionId;
	}

	void Deserialize(ByteBuffer& data)
	{
		int8 b;
		data>>b;
		success = Desperion::BooleanByteWrapper::GetFlag(b, 0);
		automaticAction = Desperion::BooleanByteWrapper::GetFlag(b, 1);
		data>>actionId;
	}
};

#endif