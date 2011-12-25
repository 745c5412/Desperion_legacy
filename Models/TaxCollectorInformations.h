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

#ifndef __TAX_COLLECTOR_INFORMATIONS__
#define __TAX_COLLECTOR_INFORMATIONS__

class TaxCollectorInformations : public DofusModel
{
public:
	int uniqueId;
	int16 firtNameId;
	int16 lastNameId;
	AdditionalTaxCollectorInformationsPtr additonalInformation;
	int16 worldX;
	int16 worldY;
	int16 subAreaId;
	int8 state;
	EntityLookPtr look;
	int kamas;
	int64 experience;
	int pods;
	int itemsValue;

	uint16 GetProtocol() const
	{ return TAX_COLLECTOR_INFORMATIONS; }

	TaxCollectorInformations()
	{
	}

	TaxCollectorInformations(int uniqueId, int16 firtNameId, int16 lastNameId, AdditionalTaxCollectorInformations* additonalInformation, int16 worldX, int16 worldY, int16 subAreaId, int8 state, EntityLook* look, int kamas, int64 experience, int pods, int itemsValue) : uniqueId(uniqueId), firtNameId(firtNameId), lastNameId(lastNameId), additonalInformation(additonalInformation), worldX(worldX), worldY(worldY), subAreaId(subAreaId), state(state), look(look), kamas(kamas), experience(experience), pods(pods), itemsValue(itemsValue)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<uniqueId<<firtNameId<<lastNameId;
		additonalInformation->Serialize(data);
		data<<worldX<<worldY<<subAreaId<<state;
		look->Serialize(data);
		data<<kamas<<experience<<pods<<itemsValue;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>uniqueId>>firtNameId>>lastNameId;
		additonalInformation.reset(new AdditionalTaxCollectorInformations);
		additonalInformation->Deserialize(data);
		data>>worldX>>worldY>>subAreaId>>state;
		look.reset(new EntityLook);
		look->Deserialize(data);
		data>>kamas>>experience>>pods>>itemsValue;
	}
};

typedef boost::shared_ptr<TaxCollectorInformations> TaxCollectorInformationsPtr;

#endif