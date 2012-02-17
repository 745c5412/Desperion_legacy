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

#ifndef __JOB_CRAFTER_DIRECTORY_SETTINGS_MESSAGE__
#define __JOB_CRAFTER_DIRECTORY_SETTINGS_MESSAGE__

class JobCrafterDirectorySettingsMessage : public DofusMessage
{
public:
	std::vector<JobCrafterDirectorySettingsPtr> craftersSettings;

	uint16 GetOpcode() const
	{ return SMSG_JOB_CRAFTER_DIRECTORY_SETTINGS; }

	JobCrafterDirectorySettingsMessage()
	{
	}

	JobCrafterDirectorySettingsMessage(std::vector<JobCrafterDirectorySettingsPtr>& craftersSettings) : craftersSettings(craftersSettings)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		uint16 size = craftersSettings.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			craftersSettings[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		craftersSettings.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			JobCrafterDirectorySettingsPtr model(new JobCrafterDirectorySettings);
			model->Deserialize(data);
			craftersSettings.push_back(model);
		}
	}
};

#endif