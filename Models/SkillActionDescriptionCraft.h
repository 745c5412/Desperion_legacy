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

#ifndef __SKILL_ACTION_DESCRIPTION_CRAFT__
#define __SKILL_ACTION_DESCRIPTION_CRAFT__

class SkillActionDescriptionCraft : public SkillActionDescription
{
public:
	int8 maxSlots;
	int8 probability;

	uint16 GetProtocol() const
	{ return SKILL_ACTION_DESCRIPTION_CRAFT; }

	SkillActionDescriptionCraft()
	{
	}

	SkillActionDescriptionCraft(int16 skillId, int8 maxSlots, int8 probability) : SkillActionDescription(skillId), maxSlots(maxSlots), probability(probability)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		SkillActionDescription::Serialize(data);
		data<<maxSlots<<probability;
	}

	void Deserialize(ByteBuffer& data)
	{
		SkillActionDescription::Deserialize(data);
		data>>maxSlots>>probability;
	}
};

typedef boost::shared_ptr<SkillActionDescriptionCraft> SkillActionDescriptionCraftPtr;

#endif