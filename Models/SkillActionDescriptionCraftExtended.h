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

#ifndef __SKILL_ACTION_DESCRIPTION_CRAFT_EXTENDED__
#define __SKILL_ACTION_DESCRIPTION_CRAFT_EXTENDED__

class SkillActionDescriptionCraftExtended : public SkillActionDescriptionCraft
{
public:
	int8 thresholdSlots;
	int8 optimumProbability;

	uint16 GetProtocol() const
	{ return SKILL_ACTION_DESCRIPTION_CRAFT_EXTENDED; }

	SkillActionDescriptionCraftExtended()
	{
	}

	SkillActionDescriptionCraftExtended(int16 skillId, int8 maxSlots, int8 probability, int8 thresholdSlots, int8 optimumProbability) : SkillActionDescriptionCraft(skillId, maxSlots, probability), thresholdSlots(thresholdSlots), optimumProbability(optimumProbability)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		SkillActionDescriptionCraft::Serialize(data);
		data<<thresholdSlots<<optimumProbability;
	}

	void Deserialize(ByteBuffer& data)
	{
		SkillActionDescriptionCraft::Deserialize(data);
		data>>thresholdSlots>>optimumProbability;
	}
};

typedef boost::shared_ptr<SkillActionDescriptionCraftExtended> SkillActionDescriptionCraftExtendedPtr;

#endif