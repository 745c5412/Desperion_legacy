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

#ifndef __JOB_CRAFTER_DIRECTORY_ENTRY_MESSAGE__
#define __JOB_CRAFTER_DIRECTORY_ENTRY_MESSAGE__

class JobCrafterDirectoryEntryMessage : public DofusMessage
{
public:
	JobCrafterDirectoryEntryPlayerInfoPtr playerInfo;
	std::vector<JobCrafterDirectoryEntryJobInfoPtr> jobInfoList;
	EntityLookPtr playerLook;

	uint16 GetOpcode() const
	{ return SMSG_JOB_CRAFTER_DIRECTORY_ENTRY; }

	JobCrafterDirectoryEntryMessage()
	{
	}

	JobCrafterDirectoryEntryMessage(JobCrafterDirectoryEntryPlayerInfo* playerInfo, std::vector<JobCrafterDirectoryEntryJobInfoPtr>& jobInfoList, EntityLook* playerLook) : playerInfo(playerInfo), jobInfoList(jobInfoList), playerLook(playerLook)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		playerInfo->Serialize(data);
		uint16 size = jobInfoList.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			jobInfoList[a]->Serialize(data);
		playerLook->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		playerInfo.reset(new JobCrafterDirectoryEntryPlayerInfo);
		playerInfo->Deserialize(data);
		jobInfoList.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			JobCrafterDirectoryEntryJobInfoPtr model(new JobCrafterDirectoryEntryJobInfo);
			model->Deserialize(data);
			jobInfoList.push_back(model);
		}
		playerLook.reset(new EntityLook);
		playerLook->Deserialize(data);
	}
};

#endif