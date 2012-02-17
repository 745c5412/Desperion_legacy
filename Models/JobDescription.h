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

#ifndef __JOB_DESCRIPTION__
#define __JOB_DESCRIPTION__

class JobDescription : public DofusModel
{
public:
	int8 jobId;
	std::vector<SkillActionDescriptionPtr> skills;

	uint16 GetProtocol() const
	{ return JOB_DESCRIPTION; }

	JobDescription()
	{
	}

	JobDescription(int8 jobId, std::vector<SkillActionDescriptionPtr>& skills) : jobId(jobId), skills(skills)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<jobId;
		uint16 size = skills.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
		{
			data<<skills[a]->GetProtocol();
			skills[a]->Serialize(data);
		}
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>jobId;
		skills.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			uint16 protocol;
			data>>protocol;
			SkillActionDescriptionPtr model(Desperion::ProtocolTypeManager::GetSkillActionDescription(protocol));
			model->Deserialize(data);
			skills.push_back(model);
		}
	}
};

typedef boost::shared_ptr<JobDescription> JobDescriptionPtr;

#endif