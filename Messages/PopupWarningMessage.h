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

#ifndef __POPUP_WARNING_MESSAGE__
#define __POPUP_WARNING_MESSAGE__

class PopupWarningMessage : public DofusMessage
{
public:
	uint8 lockDuration;
	std::string author;
	std::string content;

	uint16 GetOpcode() const
	{ return SMSG_POPUP_WARNING; }

	PopupWarningMessage()
	{
	}

	PopupWarningMessage(uint8 lockDuration, std::string author, std::string content) : lockDuration(lockDuration), author(author), content(content)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<lockDuration<<author<<content;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>lockDuration>>author>>content;
	}
};

#endif