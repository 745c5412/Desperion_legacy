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

#ifndef __CHARACTER_BASE_CHARACTERISTIC__
#define __CHARACTER_BASE_CHARACTERISTIC__

class CharacterBaseCharacteristic : public DofusModel
{
public:
	int16 base;
	int16 objectsAndMountBonus;
	int16 alignGiftBonus;
	int16 contextModif;

	uint16 GetProtocol() const
	{ return CHARACTER_BASE_CHARACTERISTIC; }

	CharacterBaseCharacteristic()
	{
	}

	CharacterBaseCharacteristic(int16 base, int16 objectsAndMountBonus, int16 alignGiftBonus, int16 contextModif) : base(base), objectsAndMountBonus(objectsAndMountBonus), alignGiftBonus(alignGiftBonus), contextModif(contextModif)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<base<<objectsAndMountBonus<<alignGiftBonus<<contextModif;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>base>>objectsAndMountBonus>>alignGiftBonus>>contextModif;
	}
};

typedef boost::shared_ptr<CharacterBaseCharacteristic> CharacterBaseCharacteristicPtr;

#endif