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

#ifndef __JOB_CRAFTER_DIRECTORY_LIST_ENTRY__
#define __JOB_CRAFTER_DIRECTORY_LIST_ENTRY__

class JobCrafterDirectoryListEntry : public DofusModel
{
public:
	JobCrafterDirectoryEntryPlayerInfoPtr playerInfo;
	JobCrafterDirectoryEntryJobInfoPtr jobInfo;

	uint16 GetProtocol() const
	{ return JOB_CRAFTER_DIRECTORY_LIST_ENTRY; }

	JobCrafterDirectoryListEntry()
	{
	}

	JobCrafterDirectoryListEntry(JobCrafterDirectoryEntryPlayerInfo* playerInfo, JobCrafterDirectoryEntryJobInfo* jobInfo) : playerInfo(playerInfo), jobInfo(jobInfo)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		playerInfo->Serialize(data);
		jobInfo->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		playerInfo.reset(new JobCrafterDirectoryEntryPlayerInfo);
		playerInfo->Deserialize(data);
		jobInfo.reset(new JobCrafterDirectoryEntryJobInfo);
		jobInfo->Deserialize(data);
	}
};

typedef boost::shared_ptr<JobCrafterDirectoryListEntry> JobCrafterDirectoryListEntryPtr;

#endif