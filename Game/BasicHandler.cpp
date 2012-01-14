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

#include "StdAfx.h"

void Session::HandleBasicPingMessage(ByteBuffer& packet)
{
	BasicPingMessage data;
	data.Deserialize(packet);

	Send(BasicPongMessage(data.quiet));
}

void Session::HandleNumericWhoIsRequestMessage(ByteBuffer& packet)
{
	NumericWhoIsRequestMessage data;
	data.Deserialize(packet);

	Session* s = NULL;
	CharacterMinimals* c = World::Instance().GetCharacterMinimals(data.playerId);
	if(c != NULL && c->onlineCharacter != NULL)
		s = c->onlineCharacter->GetSession();

	if(s == NULL)
		return;
	Send(NumericWhoIsMessage(c->id, s->GetData(FLAG_GUID).intValue));
}

void Session::HandleBasicWhoIsRequestMessage(ByteBuffer& packet)
{
	BasicWhoIsRequestMessage data;
	data.Deserialize(packet);

	Session* s = SearchForSession(data.search);
	if(s == NULL)
	{
		Send(BasicWhoIsNoMatchMessage(data.search));
		return;
	}
	Send(BasicWhoIsMessage(false, 0, s->GetData(FLAG_PSEUDO).stringValue, s->GetCharacter()->GetName(),
		s->GetCharacter()->GetMap()->GetSubAreaId()));
}

void Session::HandleBasicWhoAmIRequestMessage(ByteBuffer& packet)
{
	BasicWhoAmIRequestMessage data;
	data.Deserialize(packet);

	Send(BasicWhoIsMessage(true, 0, m_data[FLAG_PSEUDO].stringValue, m_char->GetName(), m_char->GetMap()->GetSubAreaId()));
}