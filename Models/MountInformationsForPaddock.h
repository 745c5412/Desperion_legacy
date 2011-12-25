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

#ifndef __MOUNT_INFORMATIONS_FOR_PADDOCK__
#define __MOUNT_INFORMATIONS_FOR_PADDOCK__

class MountInformationsForPaddock : public DofusModel
{
public:
	int modelId;
	std::string name;
	std::string ownerName;

	uint16 GetProtocol() const
	{ return MOUNT_INFORMATIONS_FOR_PADDOCK; }

	MountInformationsForPaddock()
	{
	}

	MountInformationsForPaddock(int modelId, std::string name, std::string ownerName) : modelId(modelId), name(name), ownerName(ownerName)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<modelId<<name<<ownerName;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>modelId>>name>>ownerName;
	}
};

typedef boost::shared_ptr<MountInformationsForPaddock> MountInformationsForPaddockPtr;

#endif