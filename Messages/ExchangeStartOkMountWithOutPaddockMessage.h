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

#ifndef __EXCHANGE_START_OK_MOUNT_WITH_OUT_PADDOCK_MESSAGE__
#define __EXCHANGE_START_OK_MOUNT_WITH_OUT_PADDOCK_MESSAGE__

class ExchangeStartOkMountWithOutPaddockMessage : public DofusMessage
{
public:
	std::vector<MountClientDataPtr> stabledMountsDescription;

	uint16 GetOpcode() const
	{ return SMSG_EXCHANGE_START_OK_MOUNT_WITH_OUT_PADDOCK; }

	ExchangeStartOkMountWithOutPaddockMessage()
	{
	}

	ExchangeStartOkMountWithOutPaddockMessage(std::vector<MountClientDataPtr>& stabledMountsDescription) : stabledMountsDescription(stabledMountsDescription)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		uint16 size = stabledMountsDescription.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			stabledMountsDescription[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		stabledMountsDescription.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			MountClientDataPtr model(new MountClientData);
			model->Deserialize(data);
			stabledMountsDescription.push_back(model);
		}
	}
};

#endif