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

#ifndef __IDENTIFICATION_MESSAGE__
#define __IDENTIFICATION_MESSAGE__

class IdentificationMessage : public DofusMessage
{
public:
	VersionPtr version;
	std::string login;
	std::vector<int8> credentials;
	std::string lang;
	bool autoConnect, useCertificate, useLoginToken;
	int16 serverId;

	virtual uint16 GetOpcode() const
	{ return CMSG_IDENTIFICATION; }

	IdentificationMessage()
	{
	}

	IdentificationMessage(bool autoConnect, bool useLoginToken, bool useCertificate, Version* version, 
		std::string lang, std::string login, std::vector<int8>& credentials, int16 serverId) : autoConnect(autoConnect),
		useLoginToken(useLoginToken), useCertificate(useCertificate), version(version), lang(lang),
		login(login), credentials(credentials), serverId(serverId)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		uint8 byte;
		Desperion::BooleanByteWrapper::SetFlag(byte, 0, autoConnect);
		Desperion::BooleanByteWrapper::SetFlag(byte, 1, useLoginToken);
		Desperion::BooleanByteWrapper::SetFlag(byte, 2, useCertificate);
		data<<byte;
		version->Serialize(data);
		data<<lang<<login;
		uint16 size = credentials.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			data<<credentials[a];
		data<<serverId;
	}

	void Deserialize(ByteBuffer& data)
	{
		credentials.clear();
		uint8 byte;
		data>>byte;
		autoConnect = Desperion::BooleanByteWrapper::GetFlag(byte, 0);
		useLoginToken = Desperion::BooleanByteWrapper::GetFlag(byte, 1);
		useCertificate = Desperion::BooleanByteWrapper::GetFlag(byte, 2);
		version.reset(new Version);
		version->Deserialize(data);
		data>>lang>>login;
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int8 cred;
			data>>cred;
			credentials.push_back(cred);
		}
		data>>serverId;
	}
};

#endif