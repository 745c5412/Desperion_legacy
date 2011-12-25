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

#ifndef __SKILL_ACTION_DESCRIPTION_COLLECT__
#define __SKILL_ACTION_DESCRIPTION_COLLECT__

class SkillActionDescriptionCollect : public SkillActionDescriptionTimed
{
public:
	int16 min;
	int16 max;

	uint16 GetProtocol() const
	{ return SKILL_ACTION_DESCRIPTION_COLLECT; }

	SkillActionDescriptionCollect()
	{
	}

	SkillActionDescriptionCollect(int16 skillId, uint8 time, int16 min, int16 max) : SkillActionDescriptionTimed(skillId, time), min(min), max(max)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		SkillActionDescriptionTimed::Serialize(data);
		data<<min<<max;
	}

	void Deserialize(ByteBuffer& data)
	{
		SkillActionDescriptionTimed::Deserialize(data);
		data>>min>>max;
	}
};

typedef boost::shared_ptr<SkillActionDescriptionCollect> SkillActionDescriptionCollectPtr;

#endif