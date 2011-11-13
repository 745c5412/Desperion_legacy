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

#ifndef __IDENTIFICATION_WITH_SERVER_ID_MESSAGE__
#define __IDENTIFICATION_WITH_SERVER_ID_MESSAGE__

class IdentificationWithServerIdMessage : public IdentificationMessage
{
public:
	int16 serverId;

	virtual uint16 GetOpcode() const
	{ return CMSG_IDENTIFICATION_WITH_SERVER_ID; }

	IdentificationWithServerIdMessage()
	{
	}

	IdentificationWithServerIdMessage(Version* version, std::vector<TrustCertificatePtr>& certificates, std::string userName,
		std::string password, bool autoConnect, int16 serverId) : IdentificationMessage(version, certificates, userName, password,
		autoConnect), serverId(serverId)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		IdentificationMessage::Serialize(data);
		data<<serverId;
	}

	void Deserialize(ByteBuffer& data)
	{
		IdentificationMessage::Deserialize(data);
		data>>serverId;
	}
};

#endif