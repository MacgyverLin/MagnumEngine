///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited			 //
//																 //
// Author : Mac Lin									             //
// Module : EpicForceEngine										 //
// Date   : 19/Aug/2011											 //
//																 //
///////////////////////////////////////////////////////////////////
#ifndef _HeightFieldShape3_h_
#define _HeightFieldShape3_h_

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
class HeightFieldShape3
#else
class HeightFieldShape3 : public Shape3
#endif
{
public:
	class Resource;
	class ResourceImporter;

	class Data
	{
	friend class HeightFieldShape3Builder;
	friend class HeightFieldShape3;
	friend class HeightFieldShape3::Resource;
	friend class HeightFieldShape3::ResourceImporter;
	public:
		Data();
		~Data();

		void read(InputStream &is); 
		void write(OutputStream &os) const;

		const Vector3 &getOrigin() const
		{
			return origin;
		}
	private:
		int						version;
		Platform				platform;

		int numGridX;
		int numGridZ;
		float gridSizeX;
		float gridSizeZ;
		float minHeight;
		float maxHeight;
		Vector3 origin;
		Vector<float>			heights;
		Vector<unsigned char>	materialIDs;

		void *shape;
	};

#ifdef EXPORTER
#else
	class Resource : public ResourceAccess
	{
	friend class HeightFieldShape3Builder;
	friend class HeightFieldShape3;
	friend class HeightFieldShape3::Resource;
	friend class HeightFieldShape3::ResourceImporter;
	public:
		Resource(const char *path_);
		virtual ~Resource();

		DECLARE_RESOURCE(HeightFieldShape3::Resource, heightfield)
	protected:
		virtual unsigned char *onCreate(int length);
		virtual void onLoaded();
		virtual void onDestroy();
	private:
	private:
		HeightFieldShape3::Data			data;
		Vector<unsigned char>			buffer;
	};

	#ifdef ENABLE_RESOURCE_IMPORT
	class ResourceImporter : public ResourceImport
	{
	friend class HeightFieldShape3Builder;
	friend class HeightFieldShape3;
	friend class HeightFieldShape3::Resource;
	friend class HeightFieldShape3::ResourceImporter;
	public:
		ResourceImporter(const char *path_);
		virtual ~ResourceImporter();

		DECLARE_RESOURCE_IMPORT(HeightFieldShape3::ResourceImporter, heightfield, heightfield)
	
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
	HeightFieldShape3();
	~HeightFieldShape3();

	bool construct(const char *path_);
	void destruct();

	const Vector3 &getOrigin() const
	{
		assert(resource);

		return resource->data.getOrigin();
	}

	virtual void getMassProp(float density, float &mass, Vector3 &localInertia) const;
	//virtual int32 GetChildCount() const = 0;
	//virtual bool TestPoint(const b2Transform& xf, const b2Vec2& p) const = 0;
	//virtual bool RayCast(b2RayCastOutput* output, const b2RayCastInput& input, const b2Transform& transform, int32 childIndex) const = 0;
	//virtual void ComputeAABB(b2AABB* aabb, const b2Transform& xf, int32 childIndex) const = 0;
	//virtual void ComputeMass(b2MassData* massData, float32 density) const = 0;
protected:
private:
	HeightFieldShape3::Resource *resource;
#endif
};

};

#endif