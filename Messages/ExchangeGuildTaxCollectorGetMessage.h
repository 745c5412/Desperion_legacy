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

#ifndef __EXCHANGE_GUILD_TAX_COLLECTOR_GET_MESSAGE__
#define __EXCHANGE_GUILD_TAX_COLLECTOR_GET_MESSAGE__

class ExchangeGuildTaxCollectorGetMessage : public DofusMessage
{
public:
	std::string collectorName;
	int16 worldX;
	int16 worldY;
	int mapId;
	int16 subAreaId;
	std::string userName;
	int64 experience;
	std::vector<ObjectItemQuantityPtr> objectsInfos;

	uint16 GetOpcode() const
	{ return SMSG_EXCHANGE_GUILD_TAX_COLLECTOR_GET; }

	ExchangeGuildTaxCollectorGetMessage()
	{
	}

	ExchangeGuildTaxCollectorGetMessage(std::string collectorName, int16 worldX, int16 worldY, int mapId, int16 subAreaId, std::string userName, int64 experience, std::vector<ObjectItemQuantityPtr>& objectsInfos) : collectorName(collectorName), worldX(worldX), worldY(worldY), mapId(mapId), subAreaId(subAreaId), userName(userName), experience(experience), objectsInfos(objectsInfos)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<collectorName<<worldX<<worldY<<mapId<<subAreaId<<userName<<experience;
		uint16 size = objectsInfos.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			objectsInfos[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>collectorName>>worldX>>worldY>>mapId>>subAreaId>>userName>>experience;
		objectsInfos.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			ObjectItemQuantityPtr model(new ObjectItemQuantity);
			model->Deserialize(data);
			objectsInfos.push_back(model);
		}
	}
};

#endif