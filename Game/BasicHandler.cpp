#include "StdAfx.h"

void Session::HandleBasicPingMessage(ByteBuffer& packet)
{
	BasicPingMessage data(packet);
	Send(BasicPongMessage(data.quiet));
}