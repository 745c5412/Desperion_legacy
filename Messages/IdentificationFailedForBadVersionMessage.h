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

#ifndef __IDENTIFICATION_FAILED_FOR_BAD_VERSION_MESSAGE__
#define __IDENTIFICATION_FAILED_FOR_BAD_VERSION_MESSAGE__

class IdentificationFailedForBadVersionMessage : public IdentificationFailedMessage
{
public:
	VersionPtr requiredVersion;

	uint16 GetOpcode() const
	{ return SMSG_IDENTIFICATION_FAILED_FOR_BAD_VERSION; }

	IdentificationFailedForBadVersionMessage()
	{
	}

	IdentificationFailedForBadVersionMessage(int8 reason, Version* requiredVersion) : IdentificationFailedMessage(reason), requiredVersion(requiredVersion)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		IdentificationFailedMessage::Serialize(data);
		requiredVersion->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		IdentificationFailedMessage::Deserialize(data);
		requiredVersion.reset(new Version);
		requiredVersion->Deserialize(data);
	}
};

#endif