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

#ifndef __JOB_CRAFTER_DIRECTORY_ENTRY_JOB_INFO__
#define __JOB_CRAFTER_DIRECTORY_ENTRY_JOB_INFO__

class JobCrafterDirectoryEntryJobInfo : public DofusModel
{
public:
	int8 jobId;
	int8 jobLevel;
	int8 userDefinedParams;
	int8 minSlots;

	uint16 GetProtocol() const
	{ return JOB_CRAFTER_DIRECTORY_ENTRY_JOB_INFO; }

	JobCrafterDirectoryEntryJobInfo()
	{
	}

	JobCrafterDirectoryEntryJobInfo(int8 jobId, int8 jobLevel, int8 userDefinedParams, int8 minSlots) : jobId(jobId), jobLevel(jobLevel), userDefinedParams(userDefinedParams), minSlots(minSlots)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<jobId<<jobLevel<<userDefinedParams<<minSlots;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>jobId>>jobLevel>>userDefinedParams>>minSlots;
	}
};

typedef boost::shared_ptr<JobCrafterDirectoryEntryJobInfo> JobCrafterDirectoryEntryJobInfoPtr;

#endif