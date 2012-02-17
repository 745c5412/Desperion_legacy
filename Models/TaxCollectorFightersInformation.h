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

#ifndef __TAX_COLLECTOR_FIGHTERS_INFORMATION__
#define __TAX_COLLECTOR_FIGHTERS_INFORMATION__

class TaxCollectorFightersInformation : public DofusModel
{
public:
	int collectorId;
	std::vector<CharacterMinimalPlusLookInformationsPtr> allyCharactersInformations;
	std::vector<CharacterMinimalPlusLookInformationsPtr> enemyCharactersInformations;

	uint16 GetProtocol() const
	{ return TAX_COLLECTOR_FIGHTERS_INFORMATION; }

	TaxCollectorFightersInformation()
	{
	}

	TaxCollectorFightersInformation(int collectorId, std::vector<CharacterMinimalPlusLookInformationsPtr>& allyCharactersInformations, std::vector<CharacterMinimalPlusLookInformationsPtr>& enemyCharactersInformations) : collectorId(collectorId), allyCharactersInformations(allyCharactersInformations), enemyCharactersInformations(enemyCharactersInformations)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<collectorId;
		uint16 size = allyCharactersInformations.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			allyCharactersInformations[a]->Serialize(data);
		uint16 size = enemyCharactersInformations.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			enemyCharactersInformations[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>collectorId;
		allyCharactersInformations.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			CharacterMinimalPlusLookInformationsPtr model(new CharacterMinimalPlusLookInformations);
			model->Deserialize(data);
			allyCharactersInformations.push_back(model);
		}
		enemyCharactersInformations.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			CharacterMinimalPlusLookInformationsPtr model(new CharacterMinimalPlusLookInformations);
			model->Deserialize(data);
			enemyCharactersInformations.push_back(model);
		}
	}
};

typedef boost::shared_ptr<TaxCollectorFightersInformation> TaxCollectorFightersInformationPtr;

#endif