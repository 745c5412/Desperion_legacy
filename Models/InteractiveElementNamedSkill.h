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

#ifndef __INTERACTIVE_ELEMENT_NAMED_SKILL__
#define __INTERACTIVE_ELEMENT_NAMED_SKILL__

class InteractiveElementNamedSkill : public InteractiveElementSkill
{
public:
	int nameId;

	uint16 GetProtocol() const
	{ return INTERACTIVE_ELEMENT_NAMED_SKILL; }

	InteractiveElementNamedSkill()
	{
	}

	InteractiveElementNamedSkill(int skillId, int skillInstanceUid, int nameId) : InteractiveElementSkill(skillId, skillInstanceUid), nameId(nameId)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		InteractiveElementSkill::Serialize(data);
		data<<nameId;
	}

	void Deserialize(ByteBuffer& data)
	{
		InteractiveElementSkill::Deserialize(data);
		data>>nameId;
	}
};

typedef boost::shared_ptr<InteractiveElementNamedSkill> InteractiveElementNamedSkillPtr;

#endif