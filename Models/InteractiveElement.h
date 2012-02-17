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

#ifndef __INTERACTIVE_ELEMENT__
#define __INTERACTIVE_ELEMENT__

class InteractiveElement : public DofusModel
{
public:
	int elementId;
	int elementTypeId;
	std::vector<InteractiveElementSkillPtr> enabledSkills;
	std::vector<InteractiveElementSkillPtr> disabledSkills;

	uint16 GetProtocol() const
	{ return INTERACTIVE_ELEMENT; }

	InteractiveElement()
	{
	}

	InteractiveElement(int elementId, int elementTypeId, std::vector<InteractiveElementSkillPtr>& enabledSkills, std::vector<InteractiveElementSkillPtr>& disabledSkills) : elementId(elementId), elementTypeId(elementTypeId), enabledSkills(enabledSkills), disabledSkills(disabledSkills)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<elementId<<elementTypeId;
		uint16 size = enabledSkills.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
		{
			data<<enabledSkills[a]->GetProtocol();
			enabledSkills[a]->Serialize(data);
		}
		size = disabledSkills.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
		{
			data<<disabledSkills[a]->GetProtocol();
			disabledSkills[a]->Serialize(data);
		}
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>elementId>>elementTypeId;
		enabledSkills.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			uint16 protocol;
			data>>protocol;
			InteractiveElementSkillPtr model(Desperion::ProtocolTypeManager::GetInteractiveElementSkill(protocol));
			model->Deserialize(data);
			enabledSkills.push_back(model);
		}
		disabledSkills.clear();
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			uint16 protocol;
			data>>protocol;
			InteractiveElementSkillPtr model(Desperion::ProtocolTypeManager::GetInteractiveElementSkill(protocol));
			model->Deserialize(data);
			disabledSkills.push_back(model);
		}
	}
};

typedef boost::shared_ptr<InteractiveElement> InteractiveElementPtr;

#endif