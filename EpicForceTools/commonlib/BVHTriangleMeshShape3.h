///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited			 //
//																 //
// Author : Mac Lin									             //
// Module : EpicForceEngine										 //
// Date   : 19/Aug/2011											 //
//																 //
///////////////////////////////////////////////////////////////////
#ifndef _BVHTriangleMeshShape3_h_
#define _BVHTriangleMeshShape3_h_

#include "Stage.h"
#include "Platform.h"
#include "Vector3.h"
#ifdef EXPORTER
#else
#include "ResourceAccess.h"
#include "ResourceImport.h"
#include "Shape3.h"
#endif
using namespace EpicForce;

namespace EpicForce
{

#ifdef EXPORTER
class BVHTriangleMeshShape3
#else
class BVHTriangleMeshShape3 : public Shape3
#endif
{
public:
	class Resource;
	class ResourceImporter;

	class CustomMaterial
	{
	public:
		CustomMaterial();

		void read(InputStream &is);
		void write(OutputStream &os) const;

		float friction;
		float restitution;
		unsigned int group;
		unsigned int mask;
		unsigned int tag;
	};

	class Data
	{
	friend class BVHTriangleMeshShape3Builder;
	friend class BVHTriangleMeshShape3;
	friend class BVHTriangleMeshShape3::Resource;
	friend class BVHTriangleMeshShape3::ResourceImporter;
	public:
		Data();
		~Data();

		void read(InputStream &is);
		void write(OutputStream &os) const;
	private:
		int						version;
		Platform				platform;

		Vector<Vector3>			vertices;
		Vector<int>				indices;
		Vector<CustomMaterial>	materials;
		Vector<int>				materialIDs;

		void *indexVertexArrays;
		void *shape;
	};

#ifdef EXPORTER
#else
	class Resource : public ResourceAccess
	{
	friend class BVHTriangleMeshShape3Builder;
	friend class BVHTriangleMeshShape3;
	friend class BVHTriangleMeshShape3::Resource;
	friend class BVHTriangleMeshShape3::ResourceImporter;
	public:
		Resource(const char *path_);
		virtual ~Resource();

		DECLARE_RESOURCE(BVHTriangleMeshShape3::Resource, heightfield)
	protected:
		virtual unsigned char *onCreate(int length);
		virtual void onLoaded();
		virtual void onDestroy();
	private:
	private:
		BVHTriangleMeshShape3::Data			data;
		Vector<unsigned char>			buffer;
	};

	#ifdef ENABLE_RESOURCE_IMPORT
	class ResourceImporter : public ResourceImport
	{
	friend class BVHTriangleMeshShape3Builder;
	friend class BVHTriangleMeshShape3;
	friend class BVHTriangleMeshShape3::Resource;
	friend class BVHTriangleMeshShape3::ResourceImporter;
	public:
		ResourceImporter(const char *path_);
		virtual ~ResourceImporter();

		DECLARE_RESOURCE_IMPORT(BVHTriangleMeshShape3::ResourceImporter, heightfield, heightfield)
	
		static bool initiate();
		static void terminate();
	protected:
		virtual bool onExportFile(const char *srcFilename_, const char *dstFilename_);
		virtual bool onDeleteFile(const char *srcFilename_);
	private:
	public:
	};
	#endif

//////////////////////////////////////////////////////////////////
public:
	BVHTriangleMeshShape3();
	~BVHTriangleMeshShape3();

	bool construct(const char *path_);
	void destruct();

	//virtual int32 GetChildCount() const = 0;
	//virtual bool TestPoint(const b2Transform& xf, const b2Vec2& p) const = 0;
	//virtual bool RayCast(b2RayCastOutput* output, const b2RayCastInput& input, const b2Transform& transform, int32 childIndex) const = 0;
	//virtual void ComputeAABB(b2AABB* aabb, const b2Transform& xf, int32 childIndex) const = 0;
	//virtual void ComputeMass(b2MassData* massData, float32 density) const = 0;
protected:
private:
	BVHTriangleMeshShape3::Resource *resource;
#endif
};

};

#endif