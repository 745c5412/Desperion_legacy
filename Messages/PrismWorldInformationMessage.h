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

#ifndef __PRISM_WORLD_INFORMATION_MESSAGE__
#define __PRISM_WORLD_INFORMATION_MESSAGE__

class PrismWorldInformationMessage : public DofusMessage
{
public:
	int nbSubOwned;
	int subTotal;
	int maxSub;
	std::vector<PrismSubAreaInformationPtr> subAreasInformation;
	int nbConqsOwned;
	int conqsTotal;
	std::vector<VillageConquestPrismInformationPtr> conquetesInformation;

	uint16 GetOpcode() const
	{ return SMSG_PRISM_WORLD_INFORMATION; }

	PrismWorldInformationMessage()
	{
	}

	PrismWorldInformationMessage(int nbSubOwned, int subTotal, int maxSub, std::vector<PrismSubAreaInformationPtr>& subAreasInformation, int nbConqsOwned, int conqsTotal, std::vector<VillageConquestPrismInformationPtr>& conquetesInformation) : nbSubOwned(nbSubOwned), subTotal(subTotal), maxSub(maxSub), subAreasInformation(subAreasInformation), nbConqsOwned(nbConqsOwned), conqsTotal(conqsTotal), conquetesInformation(conquetesInformation)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<nbSubOwned<<subTotal<<maxSub;
		uint16 size = subAreasInformation.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			subAreasInformation[a]->Serialize(data);
		data<<nbConqsOwned<<conqsTotal;
		uint16 size = conquetesInformation.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			conquetesInformation[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>nbSubOwned>>subTotal>>maxSub;
		subAreasInformation.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			PrismSubAreaInformationPtr model(new PrismSubAreaInformation);
			model->Deserialize(data);
			subAreasInformation.push_back(model);
		}
		data>>nbConqsOwned>>conqsTotal;
		conquetesInformation.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			VillageConquestPrismInformationPtr model(new VillageConquestPrismInformation);
			model->Deserialize(data);
			conquetesInformation.push_back(model);
		}
	}
};

#endif