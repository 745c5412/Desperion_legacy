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

#ifndef __PADDOCK_TO_SELL_LIST_MESSAGE__
#define __PADDOCK_TO_SELL_LIST_MESSAGE__

class PaddockToSellListMessage : public DofusMessage
{
public:
	int16 pageIndex;
	int16 totalPage;
	std::vector<PaddockInformationsForSellPtr> paddockList;

	uint16 GetOpcode() const
	{ return SMSG_PADDOCK_TO_SELL_LIST; }

	PaddockToSellListMessage()
	{
	}

	PaddockToSellListMessage(int16 pageIndex, int16 totalPage, std::vector<PaddockInformationsForSellPtr>& paddockList) : pageIndex(pageIndex), totalPage(totalPage), paddockList(paddockList)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<pageIndex<<totalPage;
		uint16 size = paddockList.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			paddockList[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>pageIndex>>totalPage;
		paddockList.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			PaddockInformationsForSellPtr model(new PaddockInformationsForSell);
			model->Deserialize(data);
			paddockList.push_back(model);
		}
	}
};

#endif