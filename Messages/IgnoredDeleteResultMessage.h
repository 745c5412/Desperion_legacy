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

#ifndef __IGNORED_DELETE_RESULT_MESSAGE__
#define __IGNORED_DELETE_RESULT_MESSAGE__

class IgnoredDeleteResultMessage : public DofusMessage
{
public:
	bool success;
	bool session;
	std::string name;

	uint16 GetOpcode() const
	{ return SMSG_IGNORED_DELETE_RESULT; }

	IgnoredDeleteResultMessage()
	{
	}

	IgnoredDeleteResultMessage(bool success, bool session, std::string name) : success(success), session(session), name(name)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		int8 b = 0;
		BooleanByteWrapper::SetFlag(b, 0, success);
		BooleanByteWrapper::SetFlag(b, 1, session);
		data<<b<<name;
	}

	void Deserialize(ByteBuffer& data)
	{
		int8 b;
		data>>b;
		success = BooleanByteWrapper::GetFlag(b, 0);
		session = BooleanByteWrapper::GetFlag(b, 1);
		data>>name;
	}
};

#endif