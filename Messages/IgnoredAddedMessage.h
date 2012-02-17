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

#ifndef __IGNORED_ADDED_MESSAGE__
#define __IGNORED_ADDED_MESSAGE__

class IgnoredAddedMessage : public DofusMessage
{
public:
	IgnoredInformationsPtr ignoreAdded;
	bool session;

	uint16 GetOpcode() const
	{ return SMSG_IGNORED_ADDED; }

	IgnoredAddedMessage()
	{
	}

	IgnoredAddedMessage(IgnoredInformations* ignoreAdded, bool session) : ignoreAdded(ignoreAdded), session(session)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<ignoreAdded->GetProtocol();
		ignoreAdded->Serialize(data);
		data<<session;
	}

	void Deserialize(ByteBuffer& data)
	{
		uint16 protocol;
		data>>protocol;
		ignoreAdded.reset(Desperion::ProtocolTypeManager::GetIgnoredInformations(protocol));
		ignoreAdded->Deserialize(data);
		data>>session;
	}
};

#endif