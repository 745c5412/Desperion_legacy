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

#ifndef __STDAFX__
#define __STDAFX__

#define LOGIN_VERSION_MAJOR 0
#define LOGIN_VERSION_MINOR 5
#define LOGIN_VERSION_REVISION 1

#define REQUIRED_SHARED_VERSION_MAJOR 0
#define REQUIRED_SHARED_VERSION_MINOR 0
#define REQUIRED_SHARED_VERSION_REVISION 2

#include "../Shared/StdAfx.h"

#if SHARED_VERSION_MAJOR != REQUIRED_SHARED_VERSION_MAJOR || SHARED_VERSION_MINOR != REQUIRED_SHARED_VERSION_MINOR \
	|| SHARED_VERSION_REVISION != REQUIRED_SHARED_VERSION_REVISION
#pragma error("This Shared version isn't compatible with this Desperion version.");
#endif

#include "ConfigDefaults.h"
#include "World.h"
#include "GameServer.h"
#include "Master.h"

#include "TrustCertificate.h"
#include "SelectedServerDataMessage.h"
#include "IdentificationFailedMessage.h"
#include "Version.h"
#include "IdentificationMessage.h"
#include "IdentificationSuccessMessage.h"
#include "GameServerInformations.h"
#include "ServersListMessage.h"
#include "ProtocolRequired.h"
#include "HelloConnectMessage.h"
#include "SelectedServerRefusedMessage.h"
#include "ServerSelectionMessage.h"
#include "ServerStatusUpdateMessage.h"
#include "AcquaintanceSearchErrorMessage.h"
#include "AcquaintanceSearchMessage.h"
#include "AcquaintanceServerListMessage.h"
#include "IdentificationWithServerIdMessage.h"

#include "Session.h"
#include "GameSession.h"

#endif