///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited			 //
//																 //
// Author : Mac Lin									             //
// Module : EpicForceEngine										 //
// Date   : 19/Aug/2011											 //
//																 //
///////////////////////////////////////////////////////////////////
#include "BVHTriangleMeshShape3.h"
#ifdef EXPORTER
#else
#include "Physics3.h"
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
#include "BulletCollision\CollisionShapes\btMultimaterialTriangleMeshShape.h"
#include "BulletCollision\CollisionShapes\btTriangleIndexVertexMaterialArray.h"
#endif
using namespace EpicForce;

BVHTriangleMeshShape3::CustomMaterial::CustomMaterial()
: friction(0.9f)
, restitution(0.1f)
, group(0xffffffff)
, mask(0xffffffff)
, tag(0)
{
}

void BVHTriangleMeshShape3::CustomMaterial::read(InputStream &is)
{
	is >> friction;
	is >> restitution;
	is >> group;
	is >> mask;
	is >> tag;
}

void BVHTriangleMeshShape3::CustomMaterial::write(OutputStream &os) const
{
	os << friction;
	os << restitution;
	os << group;
	os << mask;
	os << tag;
}

/////////////////////////////////////////////////////////////////////
BVHTriangleMeshShape3::Data::Data()
: indexVertexArrays(0)
, shape(0)
{
}

BVHTriangleMeshShape3::Data::~Data()
{
#ifdef EXPORTER
#else
	if(indexVertexArrays)
	{
		delete ((btTriangleIndexVertexMaterialArray *)indexVertexArrays);
		indexVertexArrays = 0;
	}

	if(shape)
	{
		delete ((btMultimaterialTriangleMeshShape *)shape);
		shape = 0;
	}
#endif
}

void BVHTriangleMeshShape3::Data::read(InputStream &is)
{
	is >> version;
	is >> platform;

	is >> vertices;
	is >> indices;
	is >> materials;
	is >> materialIDs;

#ifdef EXPORTER
#else
	int numTriangles = indices.length() / 3;
	btTriangleIndexVertexMaterialArray *triangleIndexVertexMaterialArray = new btTriangleIndexVertexMaterialArray
	(
		numTriangles, &indices[0], sizeof(indices[0]) * 3,
		vertices.length(), &vertices[0].X(), sizeof(vertices[0]),
		materials.length(), (unsigned char *)&materials[0], sizeof(materials[0]),
		&materialIDs[0], sizeof(materialIDs[0])
	);

    bool useQuantizedAabbCompression = true;
	btMultimaterialTriangleMeshShape *trimeshShape = new btMultimaterialTriangleMeshShape
	(
		(btTriangleIndexVertexMaterialArray*)triangleIndexVertexMaterialArray, 
		useQuantizedAabbCompression
	);
    
	indexVertexArrays	= triangleIndexVertexMaterialArray;
	shape				= trimeshShape;
#endif
}

void BVHTriangleMeshShape3::Data::write(OutputStream &os) const
{
	os << version;
	os << platform;

	os << vertices;
	os << indices;
	os << materials;
	os << materialIDs;
}

////////////////////////////////////////////////////////////////
#ifdef EXPORTER
#else
BVHTriangleMeshShape3::Resource::Resource(const char *path_)
: ResourceAccess(path_)
{
}	

BVHTriangleMeshShape3::Resource::~Resource()
{
	onDestroy();
}

unsigned char *BVHTriangleMeshShape3::Resource::onCreate(int length_)
{
	buffer.resize(length_);

	return &buffer[0];
}

void BVHTriangleMeshShape3::Resource::onLoaded()
{
	MemInputStream is(&buffer[0], buffer.length());

	is >> data;
	
	buffer.destroy();
}

void BVHTriangleMeshShape3::Resource::onDestroy()
{
	buffer.destroy();
}

////////////////////////////////////////////////////////////////
#ifdef ENABLE_RESOURCE_IMPORT
BVHTriangleMeshShape3::ResourceImporter::ResourceImporter(const char *path_)
: ResourceImport(path_)
{
}

BVHTriangleMeshShape3::ResourceImporter::~ResourceImporter()
{
}

bool BVHTriangleMeshShape3::ResourceImporter::initiate()
{
	return true;
}

void BVHTriangleMeshShape3::ResourceImporter::terminate()
{
}

bool BVHTriangleMeshShape3::ResourceImporter::onExportFile(const char *srcFilename_, const char *dstFilename_)
{
	// collect Options
	this->defaultExportFileFunc(srcFilename_, dstFilename_);

	return true;
}

bool BVHTriangleMeshShape3::ResourceImporter::onDeleteFile(const char *srcFilename_)
{
	return this->defaultDeleteFileFunc(srcFilename_);
}
#endif

////////////////////////////////////////////////////////////////
BVHTriangleMeshShape3::BVHTriangleMeshShape3()
: Shape3(Shape3::HEIGHT_FIELD)
, resource(0)
{
}

BVHTriangleMeshShape3::~BVHTriangleMeshShape3()
{
	assert(handle==0);
}

bool BVHTriangleMeshShape3::construct(const char *path_)
{
	assert(resource==0);

	resource = BVHTriangleMeshShape3::Resource::get(path_);
	if(!resource)
		return false;
	resource->addRef();

	if(resource->data.shape)
	{
		handle							= resource->data.shape;

		btVector3 min, max;
		btTransform transform;
		transform.setIdentity();
		((btMultimaterialTriangleMeshShape *)handle)->getAabb(transform, min, max);

		boundingBox.Min = Vector3(min.x(), min.y(), min.z());
		boundingBox.Max = Vector3(max.x(), max.y(), max.z());
		Vector3 size(boundingBox.Max - boundingBox.Min);
	
		volume = size.X()*size.Y()*size.Z();
	}

	return handle!=0;
}

void BVHTriangleMeshShape3::destruct()
{
	if(resource)
	{
		resource->release();
		resource = 0;
	}
}
#endif