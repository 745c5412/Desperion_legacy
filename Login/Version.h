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

#ifndef __VERSION__
#define __VERSION__

class Version : public DofusModel
{
public:
	uint8 major, minor, release, patch, buildType;
	uint16 rev;

	virtual uint16 GetProtocol() const
	{ return VERSION; }

	Version()
	{
	}

	Version(uint8 major, uint8 minor, uint8 release, uint16 rev, uint8 patch, uint8 buildType) : major(major),
		minor(minor), release(release), rev(rev), patch(patch), buildType(buildType)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<major<<minor<<release<<rev<<patch<<buildType;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>major>>minor>>release>>rev>>patch>>buildType;
	}
};

typedef boost::shared_ptr<Version> VersionPtr;

#endif