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

#ifndef __UPDATE_MOUNT_INT_BOOST__
#define __UPDATE_MOUNT_INT_BOOST__

class UpdateMountIntBoost : public UpdateMountBoost
{
public:
	int value;

	uint16 GetProtocol() const
	{ return UPDATE_MOUNT_INT_BOOST; }

	UpdateMountIntBoost()
	{
	}

	UpdateMountIntBoost(int64 rideId, std::vector<UpdateMountBoostPtr>& boostToUpdateList, int value) : UpdateMountBoost(rideId, boostToUpdateList), value(value)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		UpdateMountBoost::Serialize(data);
		data<<value;
	}

	void Deserialize(ByteBuffer& data)
	{
		UpdateMountBoost::Deserialize(data);
		data>>value;
	}
};

typedef boost::shared_ptr<UpdateMountIntBoost> UpdateMountIntBoostPtr;

#endif