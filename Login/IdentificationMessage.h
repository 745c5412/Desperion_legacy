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
	std::vector<TrustCertificatePtr> certificates;
	std::string userName;
	std::string password;
	bool autoConnect;

	virtual uint16 GetOpcode() const
	{ return CMSG_IDENTIFICATION; }

	IdentificationMessage()
	{
	}

	IdentificationMessage(Version* version, std::vector<TrustCertificatePtr>& certificates, std::string userName,
		std::string password, bool autoConnect) : version(version), certificates(certificates), userName(userName), 
		password(password), autoConnect(autoConnect)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		version->Serialize(data);
		uint16 size = certificates.size();
		data<<userName<<password<<size;
		for(uint16 a = 0; a < size; ++a)
			certificates[a]->Serialize(data);
		data<<autoConnect;
	}

	void Deserialize(ByteBuffer& data)
	{
		certificates.clear();
		version.reset(new Version);
		version->Deserialize(data);

		uint16 size;
		data>>userName>>password>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			TrustCertificatePtr certif(new TrustCertificate);
			certif->Deserialize(data);
			certificates.push_back(certif);
		}
		data>>autoConnect;
	}
};

#endif