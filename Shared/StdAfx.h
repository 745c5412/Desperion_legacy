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

#ifndef __SHARED_STDAFX__
#define __SHARED_STDAFX__

#define PROTOCOL_BUILD 1428
#define PROTOCOL_REQUIRED_BUILD 1428

#define SHARED_VERSION_MAJOR 0
#define SHARED_VERSION_MINOR 0
#define SHARED_VERSION_REVISION 3

#define DOFUS_VERSION_MAJOR 2
#define DOFUS_VERSION_MINOR 5
#define DOFUS_VERSION_RELEASE 2
#define DOFUS_VERSION_REVISION 53800
#define DOFUS_VERSION_PATCH 1
#define DOFUS_VERSION_BUILD_TYPE 0

#include "Common.h"

#include "Singleton.h"
#include "MersenneTwister.h"
#include "ServerError.h"
#include "Opcodes.h"
#include "ByteBuffer.h"
#include "BooleanByteWrapper.h"
#include "Utils.inl"
#include "Singleton.h"
#include "Packet.h"
#include "SocketListener.h"
#include "Log.h"
#include "QueryResult.h"
#include "Database.h"
#include "Config.h"
#include "Timer.h"
#include "MersenneTwister.h"
#include "ProgressBar.h"
#include "DofusMessage.h"
#include "DofusModel.h"
#include "AbstractSession.h"

#endif