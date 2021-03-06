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

#ifndef __BOOLEAN_BYTE_WRAPPER__
#define __BOOLEAN_BYTE_WRAPPER__

// directement tir� du client Dofus

namespace BooleanByteWrapper
{
	inline bool GetFlag(int8 param1, int8 param2)
	{
		switch(param2)
		{
			case 0:
			{
				return (param1 & 1) != 0;
			}
			case 1:
			{
				return (param1 & 2) != 0;
			}
			case 2:
			{
				return (param1 & 4) != 0;
			}
			case 3:
			{
				return (param1 & 8) != 0;
			}
			case 4:
			{
				return (param1 & 16) != 0;
			}
			case 5:
			{
				return (param1 & 32) != 0;
			}
			case 6:
			{
				return (param1 & 64) != 0;
			}
			case 7:
			{
				return (param1 & 128) != 0;
			}
			default:
				throw std::exception("Bytes overflow");
		}
	}

	inline void SetFlag(int8& param1, int8 param2, bool param3)
	{
		switch(param2)
		{
			case 0:
			{
				if (param3)
				{
					param1 = param1 | 1;
				}
				else
				{
					param1 = param1 & 255 - 1;
				}
				break;
			}
			case 1:
			{
				if (param3)
				{
					param1 = param1 | 2;
				}
				else
				{
					param1 = param1 & 255 - 2;
				}
				break;
			}
			case 2:
			{
				if (param3)
				{
					param1 = param1 | 4;
				}
				else
				{
					param1 = param1 & 255 - 4;
				}
				break;
			}
			case 3:
			{
				if (param3)
				{
					param1 = param1 | 8;
				}
				else
				{
					param1 = param1 & 255 - 8;
				}
				break;
			}
			case 4:
			{
				if (param3)
				{
					param1 = param1 | 16;
				}
				else
				{
					param1 = param1 & 255 - 16;
				}
				break;
			}
			case 5:
			{
				if (param3)
				{
					param1 = param1 | 32;
				}
				else
				{
					param1 = param1 & 255 - 32;
				}
				break;
			}
			case 6:
			{
				if (param3)
				{
					param1 = param1 | 64;
				}
				else
				{
					param1 = param1 & 255 - 64;
				}
				break;
			}
			case 7:
			{
				if (param3)
				{
					param1 = param1 | 128;
				}
				else
				{
					param1 = param1 & 255 - 128;
				}
				break;
			}
			default:
				throw std::exception("Bytes overflow");
		}
	}
}

#endif