#include "StdAfx.h"

void Session::HandleBasicPingMessage(ByteBuffer& packet)
{
	BasicPingMessage data;
	data.Deserialize(packet);
	Send(BasicPongMessage(data.quiet));
}