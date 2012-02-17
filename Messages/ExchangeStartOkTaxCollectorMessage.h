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

#ifndef __EXCHANGE_START_OK_TAX_COLLECTOR_MESSAGE__
#define __EXCHANGE_START_OK_TAX_COLLECTOR_MESSAGE__

class ExchangeStartOkTaxCollectorMessage : public DofusMessage
{
public:
	int collectorId;
	std::vector<ObjectItemPtr> objectsInfos;
	int goldInfo;

	uint16 GetOpcode() const
	{ return SMSG_EXCHANGE_START_OK_TAX_COLLECTOR; }

	ExchangeStartOkTaxCollectorMessage()
	{
	}

	ExchangeStartOkTaxCollectorMessage(int collectorId, std::vector<ObjectItemPtr>& objectsInfos, int goldInfo) : collectorId(collectorId), objectsInfos(objectsInfos), goldInfo(goldInfo)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<collectorId;
		uint16 size = objectsInfos.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			objectsInfos[a]->Serialize(data);
		data<<goldInfo;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>collectorId;
		objectsInfos.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			ObjectItemPtr model(new ObjectItem);
			model->Deserialize(data);
			objectsInfos.push_back(model);
		}
		data>>goldInfo;
	}
};

#endif