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

#ifndef __SERVER_EXPERIENCE_MODIFICATOR_MESSAGE__
#define __SERVER_EXPERIENCE_MODIFICATOR_MESSAGE__

class ServerExperienceModificatorMessage : public DofusMessage
{
public:
	int16 experiencePercent;

	uint16 GetOpcode() const
	{ return SMSG_SERVER_EXPERIENCE_MODIFICATOR; }

	ServerExperienceModificatorMessage()
	{
	}

	ServerExperienceModificatorMessage(int16 experiencePercent) : experiencePercent(experiencePercent)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<experiencePercent;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>experiencePercent;
	}
};

#endif