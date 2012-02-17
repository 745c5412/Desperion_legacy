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

#ifndef __BASIC_LATENCY_STATS_MESSAGE__
#define __BASIC_LATENCY_STATS_MESSAGE__

class BasicLatencyStatsMessage : public DofusMessage
{
public:
	uint16 latency;
	int16 sampleCount;
	int16 max;

	uint16 GetOpcode() const
	{ return CMSG_BASIC_LATENCY_STATS; }

	BasicLatencyStatsMessage()
	{
	}

	BasicLatencyStatsMessage(uint16 latency, int16 sampleCount, int16 max) : latency(latency), sampleCount(sampleCount), max(max)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<latency<<sampleCount<<max;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>latency>>sampleCount>>max;
	}
};

#endif