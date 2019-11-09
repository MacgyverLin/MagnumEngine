///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "ResourcePath.h"
using namespace Magnum;

ResourcePath::ResourcePath(const char *extension_)
: path("default/default")
, extension(extension_)
{
}

ResourcePath::ResourcePath(const char *path_, const char *extension_)
: path(path_)
, extension(extension_)
{
}

ResourcePath::ResourcePath(const ResourcePath &resourcePath_)
{
	*this = resourcePath_;
}

ResourcePath &ResourcePath::operator = (const ResourcePath &resourcePath_)
{
	this->path		= resourcePath_.path;
	this->extension = resourcePath_.extension;

	return *this;
}

ResourcePath::~ResourcePath()
{
}

const String &ResourcePath::getPath() const
{
	return path;
}

void ResourcePath::setPath(const String &path_)
{
	path = path_;
}

const String &ResourcePath::getExtension() const
{
	return extension;
}

bool ResourcePath::operator == (const ResourcePath &resoucePath_) const
{
	return path == resoucePath_.path && extension == resoucePath_.extension;
}

bool ResourcePath::operator <  (const ResourcePath &resourcePath_) const
{
	if(path < resourcePath_.path)
	{
		return true;
	}
	else if(path == resourcePath_.path)
	{
		return extension < resourcePath_.extension;
	}

	return false;
}

void ResourcePath::read(InputStream &is)
{
	is >> path;
	is >> extension;
}

void ResourcePath::write(OutputStream &os) const
{
	os << path;
	os << extension;
}