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

#ifndef __GROUP_MONSTER_STATIC_INFORMATIONS__
#define __GROUP_MONSTER_STATIC_INFORMATIONS__

class GroupMonsterStaticInformations : public DofusModel
{
public:
	int mainCreatureGenericId;
	int8 mainCreatureGrade;
	std::vector<MonsterInGroupInformationsPtr> underlings;

	uint16 GetProtocol() const
	{ return GROUP_MONSTER_STATIC_INFORMATIONS; }

	GroupMonsterStaticInformations()
	{
	}

	GroupMonsterStaticInformations(int mainCreatureGenericId, int8 mainCreatureGrade, std::vector<MonsterInGroupInformationsPtr>& underlings) : mainCreatureGenericId(mainCreatureGenericId), mainCreatureGrade(mainCreatureGrade), underlings(underlings)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<mainCreatureGenericId<<mainCreatureGrade;
		uint16 size = underlings.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			underlings[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>mainCreatureGenericId>>mainCreatureGrade;
		underlings.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			MonsterInGroupInformationsPtr model(new MonsterInGroupInformations);
			model->Deserialize(data);
			underlings.push_back(model);
		}
	}
};

typedef boost::shared_ptr<GroupMonsterStaticInformations> GroupMonsterStaticInformationsPtr;

#endif