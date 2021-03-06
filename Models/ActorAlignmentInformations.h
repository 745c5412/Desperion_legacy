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

#ifndef __ACTOR_ALIGNMENT_INFORMATIONS__
#define __ACTOR_ALIGNMENT_INFORMATIONS__

class ActorAlignmentInformations : public DofusModel
{
public:
	int8 alignmentSide;
	int8 alignmentValue;
	int8 alignmentGrade;
	uint16 dishonor;
	int characterPower;

	uint16 GetProtocol() const
	{ return ACTOR_ALIGNMENT_INFORMATIONS; }

	ActorAlignmentInformations()
	{
	}

	ActorAlignmentInformations(int8 alignmentSide, int8 alignmentValue, int8 alignmentGrade, uint16 dishonor, int characterPower) : alignmentSide(alignmentSide), alignmentValue(alignmentValue), alignmentGrade(alignmentGrade), dishonor(dishonor), characterPower(characterPower)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<alignmentSide<<alignmentValue<<alignmentGrade<<dishonor<<characterPower;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>alignmentSide>>alignmentValue>>alignmentGrade>>dishonor>>characterPower;
	}
};

typedef boost::shared_ptr<ActorAlignmentInformations> ActorAlignmentInformationsPtr;

#endif