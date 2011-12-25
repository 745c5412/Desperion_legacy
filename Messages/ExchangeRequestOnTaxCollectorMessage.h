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

#ifndef __EXCHANGE_REQUEST_ON_TAX_COLLECTOR_MESSAGE__
#define __EXCHANGE_REQUEST_ON_TAX_COLLECTOR_MESSAGE__

class ExchangeRequestOnTaxCollectorMessage : public DofusMessage
{
public:
	int taxCollectorId;

	uint16 GetOpcode() const
	{ return CMSG_EXCHANGE_REQUEST_ON_TAX_COLLECTOR; }

	ExchangeRequestOnTaxCollectorMessage()
	{
	}

	ExchangeRequestOnTaxCollectorMessage(int taxCollectorId) : taxCollectorId(taxCollectorId)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<taxCollectorId;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>taxCollectorId;
	}
};

#endif