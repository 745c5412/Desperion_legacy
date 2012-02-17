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

#ifndef __TAX_COLLECTOR_INFORMATIONS_IN_WAIT_FOR_HELP_STATE__
#define __TAX_COLLECTOR_INFORMATIONS_IN_WAIT_FOR_HELP_STATE__

class TaxCollectorInformationsInWaitForHelpState : public TaxCollectorInformations
{
public:
	ProtectedEntityWaitingForHelpInfoPtr waitingForHelpInfo;

	uint16 GetProtocol() const
	{ return TAX_COLLECTOR_INFORMATIONS_IN_WAIT_FOR_HELP_STATE; }

	TaxCollectorInformationsInWaitForHelpState()
	{
	}

	TaxCollectorInformationsInWaitForHelpState(int id, int16 firstNameId, int16 lastNameId, uint8 level, int guildId, int uid, ProtectedEntityWaitingForHelpInfo* waitingForHelpInfo) : TaxCollectorInformations(id, firstNameId, lastNameId, level, guildId, uid), waitingForHelpInfo(waitingForHelpInfo)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		TaxCollectorInformations::Serialize(data);
		waitingForHelpInfo->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		TaxCollectorInformations::Deserialize(data);
		waitingForHelpInfo.reset(new ProtectedEntityWaitingForHelpInfo);
		waitingForHelpInfo->Deserialize(data);
	}
};

typedef boost::shared_ptr<TaxCollectorInformationsInWaitForHelpState> TaxCollectorInformationsInWaitForHelpStatePtr;

#endif