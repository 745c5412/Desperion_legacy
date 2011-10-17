/*
	This file is part of Desperion.
	Copyright 2010, 2011 LittleScaraby

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

#ifndef __IDENTIFICATION_SUCCESS_MESSAGE__
#define __IDENTIFICATION_SUCCESS_MESSAGE__

class IdentificationSuccessMessage : public DofusMessage
{
public:
	uint32 GetOpcode() const
	{ return SMSG_IDENTIFICATION_SUCCESS; }

	IdentificationSuccessMessage(int level, bool alreadyConnected, std::string pseudo, int guid, std::string question, time_t subscribeTime)
	{
		uint8 flag = 0;
		Desperion::BooleanByteWrapper::SetFlag(flag, 0, level > 0);
		Desperion::BooleanByteWrapper::SetFlag(flag, 1, alreadyConnected);
		m_buffer<<flag<<pseudo<<guid;
		m_buffer<<uint8(0)<<question<<uint64(subscribeTime * 1000);
	}
};

#endif