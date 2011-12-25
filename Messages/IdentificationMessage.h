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
	bool autoconnect;
	bool useCertificate;
	bool useLoginToken;
	VersionPtr version;
	std::string lang;
	std::string login;
	std::vector<int8> credentials;
	int16 serverId;

	uint16 GetOpcode() const
	{ return CMSG_IDENTIFICATION; }

	IdentificationMessage()
	{
	}

	IdentificationMessage(bool autoconnect, bool useCertificate, bool useLoginToken, Version* version, std::string lang, std::string login, std::vector<int8>& credentials, int16 serverId) : autoconnect(autoconnect), useCertificate(useCertificate), useLoginToken(useLoginToken), version(version), lang(lang), login(login), credentials(credentials), serverId(serverId)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		int8 b = 0;
		Desperion::BooleanByteWrapper::SetFlag(b, 0, autoconnect);
		Desperion::BooleanByteWrapper::SetFlag(b, 1, useCertificate);
		Desperion::BooleanByteWrapper::SetFlag(b, 2, useLoginToken);
		data<<b;
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
		int8 b;
		data>>b;
		autoconnect = Desperion::BooleanByteWrapper::GetFlag(b, 0);
		useCertificate = Desperion::BooleanByteWrapper::GetFlag(b, 1);
		useLoginToken = Desperion::BooleanByteWrapper::GetFlag(b, 2);
		version.reset(new Version);
		version->Deserialize(data);
		data>>lang>>login;
		credentials.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			int8 val;
			data>>val;
			credentials.push_back(val);
		}
		data>>serverId;
	}
};

#endif