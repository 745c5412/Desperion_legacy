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

#ifndef __JOB_CRAFTER_DIRECTORY_LIST_MESSAGE__
#define __JOB_CRAFTER_DIRECTORY_LIST_MESSAGE__

class JobCrafterDirectoryListMessage : public DofusMessage
{
public:
	std::vector<JobCrafterDirectoryListEntryPtr> listEntries;

	uint16 GetOpcode() const
	{ return SMSG_JOB_CRAFTER_DIRECTORY_LIST; }

	JobCrafterDirectoryListMessage()
	{
	}

	JobCrafterDirectoryListMessage(std::vector<JobCrafterDirectoryListEntryPtr>& listEntries) : listEntries(listEntries)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		uint16 size = listEntries.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			listEntries[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		listEntries.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			JobCrafterDirectoryListEntryPtr model(new JobCrafterDirectoryListEntry);
			model->Deserialize(data);
			listEntries.push_back(model);
		}
	}
};

#endif