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
	Version version;
	std::map<int, std::string> certificates;
	std::string userName;
	std::string password;
	bool autoConnect;

	uint32 GetOpcode() const
	{ return CMSG_IDENTIFICATION; }

	IdentificationMessage(ByteBuffer& data)
	{
		version.Init(data);
		uint16 certificateLength;
		data>>userName>>password>>certificateLength;
		for(uint16 a = 0; a < certificateLength; ++a)
		{
			uint32 id;
			std::string hash;
			data>>id>>hash;
			certificates[id] = hash;
		}
		data>>autoConnect;
	}
};

#endif