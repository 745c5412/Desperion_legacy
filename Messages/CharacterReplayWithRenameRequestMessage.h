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

#ifndef __CHARACTER_REPLAY_WITH_RENAME_REQUEST_MESSAGE__
#define __CHARACTER_REPLAY_WITH_RENAME_REQUEST_MESSAGE__

class CharacterReplayWithRenameRequestMessage : public CharacterReplayRequestMessage
{
public:
	std::string name;

	uint16 GetOpcode() const
	{ return CMSG_CHARACTER_REPLAY_WITH_RENAME_REQUEST; }

	CharacterReplayWithRenameRequestMessage()
	{
	}

	CharacterReplayWithRenameRequestMessage(int characterId, std::string name) : CharacterReplayRequestMessage(characterId), name(name)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		CharacterReplayRequestMessage::Serialize(data);
		data<<name;
	}

	void Deserialize(ByteBuffer& data)
	{
		CharacterReplayRequestMessage::Deserialize(data);
		data>>name;
	}
};

#endif