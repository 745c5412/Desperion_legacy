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
	int8 major;
	int8 minor;
	int8 release;
	uint16 revision;
	int8 patch;
	int8 buildType;

	uint16 GetProtocol() const
	{ return VERSION; }

	Version()
	{
	}

	Version(int8 major, int8 minor, int8 release, uint16 revision, int8 patch, int8 buildType) : major(major), minor(minor), release(release), revision(revision), patch(patch), buildType(buildType)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<major<<minor<<release<<revision<<patch<<buildType;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>major>>minor>>release>>revision>>patch>>buildType;
	}
};

typedef boost::shared_ptr<Version> VersionPtr;

#endif