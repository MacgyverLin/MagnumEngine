///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
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
using namespace Magnum;

namespace Magnum
{

/**
* BVHTriangleMeshShape3.
* This class define a BVHTriangleMesh Shape.
* @see Shape3
*/
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

		DECLARE_RESOURCE(BVHTriangleMeshShape3::Resource, bvhtrimesh)
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

		DECLARE_RESOURCE_IMPORT(BVHTriangleMeshShape3::ResourceImporter, bvhtrimesh, bvhtrimesh)
	
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
	/**
	* BVHTriangleMeshShape3 Constructor.
	* To Construct the BVHTriangleMeshShape3
	*/
	BVHTriangleMeshShape3();

	/**
	* BVHTriangleMeshShape3 Destructor.
	* To Destruct BVHTriangleMeshShape3
	*/
	~BVHTriangleMeshShape3();

	/**
	* construct the BVHTriangleMeshShape3.
	* @param path_, the path for the trimesh resource
	* @return true if success, false if fail.
	*/
	bool construct(const char *path_);

	/**
	* destruct BVHTriangleMeshShape3 and release memory its used
	*/
	void destruct();

	/**
	* calculate the mass and moment of inertia according to the shape and density
	* @param density, the density of the shape
	* @param mass, the result of the mass of the shape is returned here
	* @param localInertia, the result of the moment of inertia of the shape is returned here
	*/
	virtual void getMassProp(float density, float &mass, Vector3 &localInertia) const;
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