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

#ifndef __IDENTIFICATION_ACCOUNT_FORCE_MESSAGE__
#define __IDENTIFICATION_ACCOUNT_FORCE_MESSAGE__

class IdentificationAccountForceMessage : public IdentificationMessage
{
public:
	std::string forcedAccountLogin;

	uint16 GetOpcode() const
	{ return CMSG_IDENTIFICATION_ACCOUNT_FORCE; }

	IdentificationAccountForceMessage()
	{
	}

	IdentificationAccountForceMessage(bool autoconnect, bool useCertificate, bool useLoginToken, Version* version, std::string lang, std::string login, std::vector<int8>& credentials, int16 serverId, std::string forcedAccountLogin) : IdentificationMessage(autoconnect, useCertificate, useLoginToken, version, lang, login, credentials, serverId), forcedAccountLogin(forcedAccountLogin)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		IdentificationMessage::Serialize(data);
		data<<forcedAccountLogin;
	}

	void Deserialize(ByteBuffer& data)
	{
		IdentificationMessage::Deserialize(data);
		data>>forcedAccountLogin;
	}
};

#endif