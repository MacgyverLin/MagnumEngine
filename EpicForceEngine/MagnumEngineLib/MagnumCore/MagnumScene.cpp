///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "MagnumScene.h"
using namespace Magnum;

MagnumScene::Data::Data()
: version(0)
, platform(Platform::PC)
{
}

MagnumScene::Data::~Data()
{
}

void MagnumScene::Data::read(InputStream &is)
{
	is >> version;
	is >> platform;
	is >> buffer;
}

void MagnumScene::Data::write(OutputStream &os) const
{
	os << version;
	os << platform;
	os << buffer;
}

////////////////////////////////////////////////////////////////
MagnumScene::Resource::Resource(const char *path_)
: ResourceAccess(path_)
{
}	

MagnumScene::Resource::~Resource()
{
	onDestroy();
}

const unsigned char *MagnumScene::Resource::getBuffer() const
{
	return &buffer[0];
}

unsigned char *MagnumScene::Resource::onCreate(int length_)
{
	buffer.resize(length_);

	return &buffer[0];
}

void MagnumScene::Resource::onLoaded()
{
	MemInputStream is(&buffer[0], buffer.length());

	is >> data;
	
	buffer.destroy();
}

void MagnumScene::Resource::onDestroy()
{
	buffer.destroy();
}

#ifdef ENABLE_RESOURCE_IMPORT
MagnumScene::ResourceImporter::ResourceImporter(const char *path_)
: ResourceImport(path_)
{
}

MagnumScene::ResourceImporter::~ResourceImporter()
{
}

bool MagnumScene::ResourceImporter::initiate()
{
	return true;
}

void MagnumScene::ResourceImporter::terminate()
{
}

bool MagnumScene::ResourceImporter::onExportFile(const char *srcFilename_, const char *dstFilename_)
{
	// collect Options
	this->defaultExportFileFunc(srcFilename_, dstFilename_);

	return true;
}

bool MagnumScene::ResourceImporter::onDeleteFile(const char *srcFilename_)
{
	return this->defaultDeleteFileFunc(srcFilename_);
}
#endif

////////////////////////////////////////////////////////////////
MagnumScene::MagnumScene() 
: resource(0)
{
}

MagnumScene::~MagnumScene()
{
	destruct();
}
		
bool MagnumScene::construct(const char *path_)
{
	assert(resource==0);

	resource = MagnumScene::Resource::get(path_);
	if(!resource)
		return false;

	resource->addReference();
	return true;
}

void MagnumScene::destruct()
{
	if(resource)
	{
		resource->release();
		resource = 0;
	}
}

const unsigned char *MagnumScene::getBuffer() const
{
	if(resource)
		return resource->getBuffer();
	else
		return 0;
}