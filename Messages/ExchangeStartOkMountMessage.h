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

#ifndef __EXCHANGE_START_OK_MOUNT_MESSAGE__
#define __EXCHANGE_START_OK_MOUNT_MESSAGE__

class ExchangeStartOkMountMessage : public ExchangeStartOkMountWithOutPaddockMessage
{
public:
	std::vector<MountClientDataPtr> paddockedMountsDescription;

	uint16 GetOpcode() const
	{ return SMSG_EXCHANGE_START_OK_MOUNT; }

	ExchangeStartOkMountMessage()
	{
	}

	ExchangeStartOkMountMessage(std::vector<MountClientDataPtr>& stabledMountsDescription, std::vector<MountClientDataPtr>& paddockedMountsDescription) : ExchangeStartOkMountWithOutPaddockMessage(stabledMountsDescription), paddockedMountsDescription(paddockedMountsDescription)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		ExchangeStartOkMountWithOutPaddockMessage::Serialize(data);
		uint16 size = paddockedMountsDescription.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			paddockedMountsDescription[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		ExchangeStartOkMountWithOutPaddockMessage::Deserialize(data);
		paddockedMountsDescription.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			MountClientDataPtr model(new MountClientData);
			model->Deserialize(data);
			paddockedMountsDescription.push_back(model);
		}
	}
};

#endif