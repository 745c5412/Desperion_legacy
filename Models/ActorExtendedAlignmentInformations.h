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

#ifndef __ACTOR_EXTENDED_ALIGNMENT_INFORMATIONS__
#define __ACTOR_EXTENDED_ALIGNMENT_INFORMATIONS__

class ActorExtendedAlignmentInformations : public ActorAlignmentInformations
{
public:
	uint16 honor;
	uint16 honorGradeFloor;
	uint16 honorNextGradeFloor;
	bool pvpEnabled;

	uint16 GetProtocol() const
	{ return ACTOR_EXTENDED_ALIGNMENT_INFORMATIONS; }

	ActorExtendedAlignmentInformations()
	{
	}

	ActorExtendedAlignmentInformations(int8 alignmentSide, int8 alignmentValue, int8 alignmentGrade, uint16 dishonor, int characterPower, uint16 honor, uint16 honorGradeFloor, uint16 honorNextGradeFloor, bool pvpEnabled) : ActorAlignmentInformations(alignmentSide, alignmentValue, alignmentGrade, dishonor, characterPower), honor(honor), honorGradeFloor(honorGradeFloor), honorNextGradeFloor(honorNextGradeFloor), pvpEnabled(pvpEnabled)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		ActorAlignmentInformations::Serialize(data);
		data<<honor<<honorGradeFloor<<honorNextGradeFloor<<pvpEnabled;
	}

	void Deserialize(ByteBuffer& data)
	{
		ActorAlignmentInformations::Deserialize(data);
		data>>honor>>honorGradeFloor>>honorNextGradeFloor>>pvpEnabled;
	}
};

typedef boost::shared_ptr<ActorExtendedAlignmentInformations> ActorExtendedAlignmentInformationsPtr;

#endif