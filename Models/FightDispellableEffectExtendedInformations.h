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

#ifndef __FIGHT_DISPELLABLE_EFFECT_EXTENDED_INFORMATIONS__
#define __FIGHT_DISPELLABLE_EFFECT_EXTENDED_INFORMATIONS__

class FightDispellableEffectExtendedInformations : public DofusModel
{
public:
	int16 actionId;
	int sourceId;
	AbstractFightDispellableEffectPtr effect;

	uint16 GetProtocol() const
	{ return FIGHT_DISPELLABLE_EFFECT_EXTENDED_INFORMATIONS; }

	FightDispellableEffectExtendedInformations()
	{
	}

	FightDispellableEffectExtendedInformations(int16 actionId, int sourceId, AbstractFightDispellableEffect* effect) : actionId(actionId), sourceId(sourceId), effect(effect)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<actionId<<sourceId<<effect->GetProtocol();
		effect->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>actionId>>sourceId;
		uint16 protocol;
		data>>protocol;
		effect.reset(Desperion::ProtocolTypeManager::GetAbstractFightDispellableEffect(protocol));
		effect->Deserialize(data);
	}
};

typedef boost::shared_ptr<FightDispellableEffectExtendedInformations> FightDispellableEffectExtendedInformationsPtr;

#endif