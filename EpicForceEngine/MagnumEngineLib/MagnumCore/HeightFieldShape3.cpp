///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "HeightFieldShape3.h"
#ifdef EXPORTER
#else
#include "Physics3.h"
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
#endif
using namespace Magnum;

HeightFieldShape3::Data::Data()
: shape(0)
{
}

HeightFieldShape3::Data::~Data()
{
#ifdef EXPORTER
#else
	if(shape)
	{
		delete ((btHeightfieldTerrainShape *)shape);
		shape = 0;
	}
#endif
}

void HeightFieldShape3::Data::read(InputStream &is)
{
	is >> version;
	is >> platform;

	is >> numGridX;
	is >> numGridZ;
	is >> gridSizeX;
	is >> gridSizeZ;
	is >> heights;
	is >> materialIDs;

#ifdef EXPORTER
#else
	bool flipQuadEdges = false;
	btHeightfieldTerrainShape *heightfieldShape = new btHeightfieldTerrainShape
		(numGridX+1, numGridZ+1, &heights[0], 1, 0, 100, 1, PHY_ScalarType::PHY_FLOAT, flipQuadEdges);
	
	// scale the shape
	btVector3 localScaling = btVector3(gridSizeX, 1.0f, gridSizeZ);
	heightfieldShape->setLocalScaling(localScaling);

	shape = heightfieldShape;
#endif
}

void HeightFieldShape3::Data::write(OutputStream &os) const
{
	os << version;
	os << platform;

	os << numGridX;
	os << numGridZ;
	os << gridSizeX;
	os << gridSizeZ;
	os << heights;
	os << materialIDs;
}

////////////////////////////////////////////////////////////////
#ifdef EXPORTER
#else
HeightFieldShape3::Resource::Resource(const char *path_)
: ResourceAccess(path_)
{
}	

HeightFieldShape3::Resource::~Resource()
{
	onDestroy();
}

unsigned char *HeightFieldShape3::Resource::onCreate(int length_)
{
	buffer.resize(length_);

	return &buffer[0];
}

void HeightFieldShape3::Resource::onLoaded()
{
	MemInputStream is(&buffer[0], buffer.length());

	is >> data;
	
	buffer.destroy();
}

void HeightFieldShape3::Resource::onDestroy()
{
	buffer.destroy();
}

////////////////////////////////////////////////////////////////
#ifdef ENABLE_RESOURCE_IMPORT
HeightFieldShape3::ResourceImporter::ResourceImporter(const char *path_)
: ResourceImport(path_)
{
}

HeightFieldShape3::ResourceImporter::~ResourceImporter()
{
}

bool HeightFieldShape3::ResourceImporter::initiate()
{
	return true;
}

void HeightFieldShape3::ResourceImporter::terminate()
{
}

bool HeightFieldShape3::ResourceImporter::onExportFile(const char *srcFilename_, const char *dstFilename_)
{
	// collect Options
	this->defaultExportFileFunc(srcFilename_, dstFilename_);

	return true;
}

bool HeightFieldShape3::ResourceImporter::onDeleteFile(const char *srcFilename_)
{
	return this->defaultDeleteFileFunc(srcFilename_);
}
#endif

////////////////////////////////////////////////////////////////
HeightFieldShape3::HeightFieldShape3()
: Shape3(Shape3::HEIGHT_FIELD)
, resource(0)
{
}

HeightFieldShape3::~HeightFieldShape3()
{
	assert(handle==0);
}

bool HeightFieldShape3::construct(const char *path_)
{
	assert(resource==0);

	resource = HeightFieldShape3::Resource::get(path_);
	if(!resource)
		return false;
	resource->addReference();

	if(resource->data.shape)
	{
		handle							= resource->data.shape;

		btVector3 min, max;
		btTransform transform;
		transform.setIdentity();
		((btHeightfieldTerrainShape *)handle)->getAabb(transform, min, max);

		boundingBox.Min = Vector3(min.x(), min.y(), min.z());
		boundingBox.Max = Vector3(max.x(), max.y(), max.z());
		Vector3 size(boundingBox.Max - boundingBox.Min);
	
		volume = size.X()*size.Y()*size.Z();
	}

	return handle!=0;
}

void HeightFieldShape3::destruct()
{
	if(resource)
	{
		resource->release();
		resource = 0;
	}
}

void HeightFieldShape3::getMassProp(float density, float &mass, Vector3 &localInertia) const
{
	mass			= 0;
	localInertia	= Vector3::ZERO;
}
#endif