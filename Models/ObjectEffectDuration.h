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

#ifndef __OBJECT_EFFECT_DURATION__
#define __OBJECT_EFFECT_DURATION__

class ObjectEffectDuration : public ObjectEffect
{
public:
	int16 days;
	int16 hours;
	int16 minutes;

	uint16 GetProtocol() const
	{ return OBJECT_EFFECT_DURATION; }

	ObjectEffectDuration()
	{
	}

	ObjectEffectDuration(int16 actionId, int16 days, int16 hours, int16 minutes) : ObjectEffect(actionId), days(days), hours(hours), minutes(minutes)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		ObjectEffect::Serialize(data);
		data<<days<<hours<<minutes;
	}

	void Deserialize(ByteBuffer& data)
	{
		ObjectEffect::Deserialize(data);
		data>>days>>hours>>minutes;
	}
};

typedef boost::shared_ptr<ObjectEffectDuration> ObjectEffectDurationPtr;

#endif