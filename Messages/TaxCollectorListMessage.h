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

#ifndef __TAX_COLLECTOR_LIST_MESSAGE__
#define __TAX_COLLECTOR_LIST_MESSAGE__

class TaxCollectorListMessage : public DofusMessage
{
public:
	int8 nbcollectorMax;
	int16 taxCollectorHireCost;
	std::vector<TaxCollectorInformationsPtr> informations;
	std::vector<TaxCollectorFightersInformationPtr> fightersInformations;

	uint16 GetOpcode() const
	{ return SMSG_TAX_COLLECTOR_LIST; }

	TaxCollectorListMessage()
	{
	}

	TaxCollectorListMessage(int8 nbcollectorMax, int16 taxCollectorHireCost, std::vector<TaxCollectorInformationsPtr>& informations, std::vector<TaxCollectorFightersInformationPtr>& fightersInformations) : nbcollectorMax(nbcollectorMax), taxCollectorHireCost(taxCollectorHireCost), informations(informations), fightersInformations(fightersInformations)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<nbcollectorMax<<taxCollectorHireCost;
		uint16 size = informations.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
		{
			data<<informations[a]->GetProtocol();
			informations[a]->Serialize(data);
		}
		uint16 size = fightersInformations.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			fightersInformations[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>nbcollectorMax>>taxCollectorHireCost;
		informations.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			uint16 protocol;
			data>>protocol;
			TaxCollectorInformationsPtr model(Desperion::ProtocolTypeManager::GetTaxCollectorInformations(protocol));
			model->Deserialize(data);
			informations.push_back(model);
		}
		fightersInformations.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			TaxCollectorFightersInformationPtr model(new TaxCollectorFightersInformation);
			model->Deserialize(data);
			fightersInformations.push_back(model);
		}
	}
};

#endif