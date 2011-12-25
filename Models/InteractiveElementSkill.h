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

#ifndef __INTERACTIVE_ELEMENT_SKILL__
#define __INTERACTIVE_ELEMENT_SKILL__

class InteractiveElementSkill : public DofusModel
{
public:
	int skillId;
	int skillInstanceUid;

	uint16 GetProtocol() const
	{ return INTERACTIVE_ELEMENT_SKILL; }

	InteractiveElementSkill()
	{
	}

	InteractiveElementSkill(int skillId, int skillInstanceUid) : skillId(skillId), skillInstanceUid(skillInstanceUid)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<skillId<<skillInstanceUid;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>skillId>>skillInstanceUid;
	}
};

typedef boost::shared_ptr<InteractiveElementSkill> InteractiveElementSkillPtr;

#endif