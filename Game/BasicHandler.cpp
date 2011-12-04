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
		s->GetCharacter()->GetMap()->GetSubareaId()));
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
		s->GetCharacter()->GetMap()->GetSubareaId()));
}

void Session::HandleBasicWhoAmIRequestMessage(ByteBuffer& packet)
{
	BasicWhoAmIRequestMessage data;
	data.Deserialize(packet);

	Send(BasicWhoIsMessage(true, 0, m_data[FLAG_PSEUDO].stringValue, m_char->GetName(), m_char->GetMap()->GetSubareaId()));
}