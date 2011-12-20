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
	Send(BasicWhoIsMessage(false, 0, s->GetData(FLAG_PSEUDO).stringValue, s->GetCharacter()->GetName(),
		s->GetCharacter()->GetMap()->GetSubAreaId()));
}

void Session::HandleBasicWhoIsRequestMessage(ByteBuffer& packet)
{
	BasicWhoIsRequestMessage data;
	data.Deserialize(packet);

	Session* s = NULL;
	if(!data.search.empty())
	{
		if(data.search.size() > 2 && data.search.at(0) == '*')
		{
			s = World::Instance().GetSession(data.search);
			if(s->GetCharacter() == NULL)
				s = NULL;
		}
		else
		{
			CharacterMinimals* c = World::Instance().GetCharacterMinimals(data.search);
			if(c != NULL && c->onlineCharacter != NULL)
				s = c->onlineCharacter->GetSession();
		}
	}

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