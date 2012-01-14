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

void Session::HandleChatSmileyRequestMessage(ByteBuffer& packet)
{
	ChatSmileyRequestMessage data;
	data.Deserialize(packet);

	Send(ChatSmileyMessage(m_char->GetGuid(), data.smileyId, m_data[FLAG_GUID].intValue));
}

void Session::HandleMoodSmileyRequestMessage(ByteBuffer& packet)
{
	MoodSmileyRequestMessage data;
	data.Deserialize(packet);

	m_char->SetSmileyId(data.smileyId);
	Send(MoodSmileyResultMessage(0, data.smileyId));
}

void Session::HandleChannelEnablingMessage(ByteBuffer& packet)
{
	ChannelEnablingMessage data;
	data.Deserialize(packet);

	if(data.enable)
	{
		if(!HasChannel(data.channel))
			m_channels.insert(data.channel);
	}
	else
		RemoveChannel(data.channel);

	Send(ChannelEnablingChangeMessage(data.channel, data.enable));
}

void Session::HandleMultiMessage(ChatClientMultiMessage* data)
{
	ChatServerMessage* toSend = NULL;
	if(data->GetOpcode() == CMSG_CHAT_CLIENT_MULTI)
	{
		toSend = new ChatServerMessage(data->channel, data->content, static_cast<int>(time(NULL)), "", m_char->GetGuid(), m_char->GetName(),
			m_data[FLAG_GUID].intValue);
	}
	else if(data->GetOpcode() == CMSG_CHAT_CLIENT_MULTI_WITH_OBJECT)
	{
		toSend = new ChatServerWithObjectMessage(data->channel, data->content, static_cast<int>(time(NULL)), "", m_char->GetGuid(), m_char->GetName(),
			m_data[FLAG_GUID].intValue, ((ChatClientMultiWithObjectMessage*)data)->objects);
	}
	else
		return;

	time_t* last = &m_lastTradingChatRequest;
	time_t interval = Desperion::Config::Instance().GetParam(TRADING_FLOOD_INTERVAL_STRING, TRADING_FLOOD_INTERVAL_DEFAULT);
	switch(data->channel)
	{
	case MULTI_CHANNEL_GLOBAL:
		m_char->GetMap()->Send(*toSend);
		break;
	case MULTI_CHANNEL_SEEK:
		last = &m_lastRecruitmentChatRequest;
		interval = Desperion::Config::Instance().GetParam(RECRUITMENT_FLOOD_INTERVAL_STRING, RECRUITMENT_FLOOD_INTERVAL_DEFAULT);
	case MULTI_CHANNEL_SALES:
		{
			time_t now = time(NULL);
			if(now > *last + interval)
			{
				World::Instance().Send(*toSend); // todo: area
				*last = now;
			}
			else
			{
				std::vector<std::string> params;
				params.push_back(Desperion::ToString(*last + interval - now));
				Send(TextInformationMessage(0, 115, params));
			}
		}
		break;
	case MULTI_CHANNEL_PARTY:
		if(m_party != NULL)
			m_party->Send(*toSend);
		else
			Send(ChatErrorMessage(CHAT_ERROR_NO_PARTY));
		break;
	case MULTI_CHANNEL_ADMIN:
		if(m_data[FLAG_LEVEL].intValue > 0)
			World::Instance().Send(*toSend, true);
		break;
	default:
		break;
	}
	delete toSend;
}

void Session::HandleChatClientMultiMessage(ByteBuffer& packet)
{
	ChatClientMultiMessage data;
	data.Deserialize(packet);
	HandleMultiMessage(&data);
}

void Session::HandleChatClientMultiWithObjectMessage(ByteBuffer& packet)
{
	ChatClientMultiWithObjectMessage data;
	data.Deserialize(packet);
	HandleMultiMessage(&data);
}

void Session::HandlePrivateMessage(ChatClientPrivateMessage* data)
{
	Session* S = SearchForSession(data->receiver);
	if(S == NULL)
	{
		Send(ChatErrorMessage(CHAT_ERROR_RECEIVER_NOT_FOUND));
		return;
	}
	else if(S->GetCharacter()->GetGuid() == m_char->GetGuid())
	{
		Send(ChatErrorMessage(CHAT_ERROR_INTERIOR_MONOLOGUE));
		return;
	}
	else if(S->GetBoolValue(BOOL_AWAY) || S->IsEnnemyWith(m_data[FLAG_GUID].intValue)
		|| S->IsIgnoredWith(m_data[FLAG_GUID].intValue) || (S->GetBoolValue(BOOL_INVISIBLE)
		&& !S->IsFriendWith(m_data[FLAG_GUID].intValue)))
	{
		std::vector<std::string> args;
		args.push_back(S->GetCharacter()->GetName());
		Send(TextInformationMessage(1, 14, args));
		return;
	}
	
	ChatServerMessage* distant = NULL;
	ChatServerCopyMessage* local = NULL;

	time_t t = time(NULL);
	if(data->GetOpcode() == CMSG_CHAT_CLIENT_PRIVATE)
	{
		distant = new ChatServerMessage(PSEUDO_CHANNEL_PRIVATE, data->content, static_cast<int>(t), "", m_char->GetGuid(), m_char->GetName(),
			m_data[FLAG_GUID].intValue);
		local = new ChatServerCopyMessage(PSEUDO_CHANNEL_PRIVATE, data->content, static_cast<int>(t), "", S->GetCharacter()->GetGuid(),
			S->GetCharacter()->GetName());
	}
	else if(data->GetOpcode() == CMSG_CHAT_CLIENT_PRIVATE_WITH_OBJECT)
	{
		distant = new ChatServerWithObjectMessage(PSEUDO_CHANNEL_PRIVATE, data->content, static_cast<int>(t), "", m_char->GetGuid(), m_char->GetName(),
			m_data[FLAG_GUID].intValue, ((ChatClientPrivateWithObjectMessage*)data)->objects);
		local = new ChatServerCopyWithObjectMessage(PSEUDO_CHANNEL_PRIVATE, data->content, static_cast<int>(t), "", S->GetCharacter()->GetGuid(),
			S->GetCharacter()->GetName(), ((ChatClientPrivateWithObjectMessage*)data)->objects);
	}
	else
		return;

	S->Send(*distant);
	Send(*local);

	delete distant;
	delete local;
}

void Session::HandleChatClientPrivateMessage(ByteBuffer& packet)
{
	ChatClientPrivateMessage data;
	data.Deserialize(packet);
	HandlePrivateMessage(&data);
}

void Session::HandleChatClientPrivateWithObjectMessage(ByteBuffer& packet)
{
	ChatClientPrivateWithObjectMessage data;
	data.Deserialize(packet);
	HandlePrivateMessage(&data);
}