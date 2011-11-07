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

#ifndef __LIVING_OBJECT_DISSOCIATE_MESSAGE__
#define __LIVING_OBJECT_DISSOCIATE_MESSAGE__

class LivingObjectDissociateMessage : public DofusMessage
{
public:
	int livingUID;
	uint8 livingPosition;

	virtual uint32 GetOpcode() const
	{ return CMSG_LIVING_OBJECT_DISSOCIATE; }

	LivingObjectDissociateMessage(ByteBuffer& data)
	{
		data>>livingUID>>livingPosition;
	}
};

#endif