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

#ifndef __BASIC_WHO_IS_MESSAGE__
#define __BASIC_WHO_IS_MESSAGE__

class BasicWhoIsMessage : public DofusMessage
{
public:
	bool self;
	int8 position;
	std::string accountNickname;
	std::string characterName;
	int16 areaId;

	uint16 GetOpcode() const
	{ return SMSG_BASIC_WHO_IS; }

	BasicWhoIsMessage()
	{
	}

	BasicWhoIsMessage(bool self, int8 position, std::string accountNickname, std::string characterName, int16 areaId) : self(self), position(position), accountNickname(accountNickname), characterName(characterName), areaId(areaId)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<self<<position<<accountNickname<<characterName<<areaId;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>self>>position>>accountNickname>>characterName>>areaId;
	}
};

#endif