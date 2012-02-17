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

#ifndef __SKILL_ACTION_DESCRIPTION_TIMED__
#define __SKILL_ACTION_DESCRIPTION_TIMED__

class SkillActionDescriptionTimed : public SkillActionDescription
{
public:
	uint8 time;

	uint16 GetProtocol() const
	{ return SKILL_ACTION_DESCRIPTION_TIMED; }

	SkillActionDescriptionTimed()
	{
	}

	SkillActionDescriptionTimed(int16 skillId, uint8 time) : SkillActionDescription(skillId), time(time)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		SkillActionDescription::Serialize(data);
		data<<time;
	}

	void Deserialize(ByteBuffer& data)
	{
		SkillActionDescription::Deserialize(data);
		data>>time;
	}
};

typedef boost::shared_ptr<SkillActionDescriptionTimed> SkillActionDescriptionTimedPtr;

#endif