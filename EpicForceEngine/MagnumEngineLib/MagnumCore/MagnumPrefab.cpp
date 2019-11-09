///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "MagnumPrefab.h"
using namespace Magnum;

MagnumPrefab::Data::Data()
: version(0)
, platform(Platform::PC)
{
}

MagnumPrefab::Data::~Data()
{
}

void MagnumPrefab::Data::read(InputStream &is)
{
	is >> version;
	is >> platform;
	is >> buffer;
}

void MagnumPrefab::Data::write(OutputStream &os) const
{
	os << version;
	os << platform;
	os << buffer;
}

////////////////////////////////////////////////////////////////
MagnumPrefab::Resource::Resource(const char *path_)
: ResourceAccess(path_)
{
}	

MagnumPrefab::Resource::~Resource()
{
	onDestroy();
}

const unsigned char *MagnumPrefab::Resource::getBuffer() const
{
	return &buffer[0];
}

unsigned char *MagnumPrefab::Resource::onCreate(int length_)
{
	buffer.resize(length_);

	return &buffer[0];
}

void MagnumPrefab::Resource::onLoaded()
{
	MemInputStream is(&buffer[0], buffer.length());

	is >> data;
	
	buffer.destroy();
}

void MagnumPrefab::Resource::onDestroy()
{
	buffer.destroy();
}

#ifdef ENABLE_RESOURCE_IMPORT
MagnumPrefab::ResourceImporter::ResourceImporter(const char *path_)
: ResourceImport(path_)
{
}

MagnumPrefab::ResourceImporter::~ResourceImporter()
{
}

bool MagnumPrefab::ResourceImporter::initiate()
{
	return true;
}

void MagnumPrefab::ResourceImporter::terminate()
{
}

bool MagnumPrefab::ResourceImporter::onExportFile(const char *srcFilename_, const char *dstFilename_)
{
	// collect Options
	this->defaultExportFileFunc(srcFilename_, dstFilename_);

	return true;
}

bool MagnumPrefab::ResourceImporter::onDeleteFile(const char *srcFilename_)
{
	return this->defaultDeleteFileFunc(srcFilename_);
}
#endif

////////////////////////////////////////////////////////////////
MagnumPrefab::MagnumPrefab() 
: resource(0)
{
}

MagnumPrefab::~MagnumPrefab()
{
	destruct();
}
		
bool MagnumPrefab::construct(const char *path_)
{
	assert(resource==0);

	resource = MagnumPrefab::Resource::get(path_);
	if(!resource)
		return false;

	resource->addReference();
	return true;
}

void MagnumPrefab::destruct()
{
	if(resource)
	{
		resource->release();
		resource = 0;
	}
}

const unsigned char *MagnumPrefab::getBuffer() const
{
	if(resource)
		return resource->getBuffer();
	else
		return 0;
}