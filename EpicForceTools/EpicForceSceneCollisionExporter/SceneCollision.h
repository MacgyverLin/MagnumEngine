///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited			 //
//																 //
// Author : Mac Lin									             //
// Module : EpicForceEngine										 //
// Date   : 19/Aug/2011											 //
//																 //
///////////////////////////////////////////////////////////////////
#ifndef _SceneCollision_h_
#define _SceneCollision_h_

#include "EString.h"
#include "Array.h"
#include "Plane3.h"
#include "Platform.h"
#include "Collision.h"

#ifdef EXPORTER
#else
#include "ResourceAccess.h"
#include "ResourceImport.h"
#include "ResourcePath.h"
#endif

using namespace EpicForce;

#define SMOOTHER_WII_COLLISION

namespace EpicForce
{

class SceneCollision : public Collision
{
public:
	class Resource;
	class ResourceImporter;

	class CastInfo
	{
	public:
		CastInfo()
		: collided(false)
		, inputPosition(Vector3::ZERO)
		, inputDistance(Vector3::ZERO)
		, inputRadius(0)

		, outputPosition(Vector3::ZERO)
		, outputNormal(0)
		, outputStartOut(true)
		, outputAllSolid(false)
		, outputFraction(1)
		, outputID(0)

		, contactPoint(Vector3::ZERO)
		, contactNormal(Vector3::ZERO)
		, penetrationDepth(0)
		{
		}
		bool collided;
		Vector3 inputPosition;
		Vector3 inputDistance;
		float inputRadius;

		Vector3 outputPosition;
		Vector3 *outputNormal;
		bool outputStartOut;
		bool outputAllSolid;
		float outputFraction;
		int outputID;

		Vector3 contactPoint;
		Vector3 contactNormal;
		float penetrationDepth;
	};

	class HeightField
	{
	friend class SceneCollision;
	friend class SceneCollision::Resource;
	friend class SceneCollision::ResourceImporter;
	friend class SceneCollisionBuilder;
	public:
		enum CollisionMode
		{
			HF_CM_REPORT_LESSTHAN,    // below the ground
			HF_CM_REPORT_EQUAL,       // on the ground
			HF_CM_REPORT_GREATERTHAN, // above the ground
			HF_CM_REPORT_ALWAYS,      // always
		};

		HeightField();
		~HeightField();

		void init(float xmin_, float xmax_, float zmin_, float zmax_,
				  int numGridX_, int numGridZ_,
		          float gridSizeX_, float gridSizeZ_, 
				  const Vector<float> &heights_);

		void setEnabled(bool enabled_);
		bool getEnabled() const;

		void setMode(CollisionMode coll_mode_);
		HeightField::CollisionMode getMode();

		int getNumGridX();
		int getNumGridZ();
		float getGridSizeX();
		float getGridSizeZ();

		bool isInsideRegion(const float &x_, const float &z_);
		bool isInsideRegion(const Vector3 &point_);
		float getHeightAt(const float &x_, const float &z_);
		float getHeightAt(const Vector3 &point_);
		
		void read(InputStream &s);
		void write(OutputStream &os) const;
	protected:
		bool test(const Vector3 &point_);
		bool testSphere(SceneCollision::CastInfo &castInfo_);
	private:
	/////////////////////////////////////////////////////////////////////////
	public:
	protected:
	private:
		String name;
		bool enabled;

		float xmin, xmax, zmin, zmax;
		float gridSizeX, gridSizeZ;
		int numGridX, numGridZ;
		Vector<float> heights;

		CollisionMode collisionMode;
	};

	class HeightFieldList
	{
	friend class SceneCollision;
	friend class SceneCollision::Resource;
	friend class SceneCollision::ResourceImporter;
	friend class SceneCollisionBuilder;
	public:
		HeightFieldList();
		~HeightFieldList();

		HeightFieldList &operator += (const HeightFieldList &heightFieldList);

		int getNumHeightFields() const;
		HeightField &getHeightField(int i_);
		const HeightField &getHeightField(int i_) const;

		bool isHeightFieldExists(const char *name_) const;
		int getHeightFieldIdx(const char *name_) const;		
		void setHeightFieldEnabled(int i, bool enabled_);
		bool getHeightFieldEnabled(int i) const;

		void read(InputStream &is);
		void write(OutputStream &os) const;
	protected:
		bool test(const Vector3 &point_);
		bool testSphere(SceneCollision::CastInfo &castInfo_);
	private:
	/////////////////////////////////////////////////////////////////////////
	public:
	protected:
	private:
		Vector<HeightField> heightFields;
	};

	//////////////////////////////////////////////////////////////////////////
	class Brush
	{
	friend class SceneCollision;
	friend class SceneCollision::Resource;
	friend class SceneCollision::ResourceImporter;
	friend class SceneCollisionBuilder;
	public:
		Brush();
		~Brush();

		bool add(const Plane3 &plane_);

		void setEnabled(bool enabled_);
		bool getEnabled() const;

		void read(InputStream &is);
		void write(OutputStream &os) const;
	protected:
		void testSphere(SceneCollision::CastInfo &castInfo_);
	private:
	/////////////////////////////////////////////////////////////////////////
	public:
	protected:
	private:
		String name;
		bool enabled;

		Vector<Plane3> planes;		
	};

	class BrushList
	{
	friend class SceneCollision;
	friend class SceneCollision::Resource;
	friend class SceneCollision::ResourceImporter;
	friend class SceneCollisionBuilder;
	public:
		BrushList();
		~BrushList();

		BrushList &operator += (const BrushList &brushList);

		int getNumBrushes() const;
		Brush &getBrush(int i_);
		const Brush &getBrush(int i_) const;

		bool isBrushExists(const char *name_) const;
		int getBrushIdx(const char *name_) const;		
		void setBrushEnabled(int i, bool enabled_);
		bool getBrushEnabled(int i) const;

		void read(InputStream &is);
		void write(OutputStream &os) const;
	protected:
		bool testSphere(SceneCollision::CastInfo &castInfo_);
	private:
	/////////////////////////////////////////////////////////////////////////
	public:
	protected:
	private:
		Vector<Brush> brushes;
	};

	class Data
	{
	friend class SceneCollision;
	friend class SceneCollision::Resource;
	friend class SceneCollision::ResourceImporter;
	friend class SceneCollisionBuilder;
	public:
		Data();
		~Data();

		Data &operator += (const Data &data);

		int getNumHeightFields() const;
		HeightField &getHeightField(int i_);
		const HeightField &getHeightField(int i_) const;

		bool isHeightFieldExists(const char *name_) const;
		int getHeightFieldIdx(const char *name_) const;		
		void setHeightFieldEnabled(int i, bool enabled_);
		bool getHeightFieldEnabled(int i) const;

		int getNumBrushes() const;
		Brush &getBrush(int i_);
		const Brush &getBrush(int i_) const;

		bool isBrushExists(const char *name_) const;
		int getBrushIdx(const char *name_) const;		
		void setBrushEnabled(int i, bool enabled_);
		bool getBrushEnabled(int i) const;

		void read(InputStream &is);
		void write(OutputStream &os) const;
	protected:
		bool test(Vector3 &point_);
		bool testSphere(SceneCollision::CastInfo &castInfo_);
	private:
		Platform					platform;
		int							version;

		BrushList					brushList;
		HeightFieldList				heightFieldList;
	};

#ifdef EXPORTER
#else
	class Resource : public ResourceAccess
	{
	friend class SceneCollision;
	friend class SceneCollision::Resource;
	friend class SceneCollision::ResourceImporter;
	friend class SceneCollisionBuilder;
	public:
		Resource(const char *path_);
		virtual ~Resource();

		DECLARE_RESOURCE(SceneCollision::Resource, scecollision)

		int getNumHeightFields() const;
		HeightField &getHeightField(int i_);
		const HeightField &getHeightField(int i_) const;

		bool isHeightFieldExists(const char *name_) const;
		int getHeightFieldIdx(const char *name_) const;		
		void setHeightFieldEnabled(int i, bool enabled_);
		bool getHeightFieldEnabled(int i) const;

		int getNumBrushes() const;
		Brush &getBrush(int i_);
		const Brush &getBrush(int i_) const;

		bool isBrushExists(const char *name_) const;
		int getBrushIdx(const char *name_) const;		
		void setBrushEnabled(int i, bool enabled_);
		bool getBrushEnabled(int i) const;
	protected:
		bool test(Vector3 &point_);
		bool testSphere(SceneCollision::CastInfo &castInfo_);
	protected:
		virtual unsigned char *onCreate(int length);
		virtual void onLoaded();
		virtual void onDestroy();
	private:
		Data data;

		Vector<unsigned char>	buffer;
	};

	#ifdef ENABLE_RESOURCE_IMPORT
	class ResourceImporter : public ResourceImport
	{
	friend class SceneCollision;
	friend class SceneCollision::Resource;
	friend class SceneCollision::ResourceImporter;
	friend class SceneCollisionBuilder;
	public:
		ResourceImporter(const char *path_);
		virtual ~ResourceImporter();

		DECLARE_RESOURCE_IMPORT(SceneCollision::ResourceImporter, scenecollision, scecollision)
	
		static bool initiate();
		static void terminate();
	protected:
		virtual bool onExportFile(const char *srcFilename_, const char *dstFilename_);
		virtual bool onDeleteFile(const char *srcFilename_);
	private:
	public:
	};
	#endif
public:
	SceneCollision();
	~SceneCollision();

	static SceneCollision &instance();

	bool construct(const char *name_);
	bool append(const char *name_);
	void destruct();

	bool test(Vector3 &point_);
	bool testSphere(SceneCollision::CastInfo &castInfo_);
protected:
private:
	SceneCollision::Data sceneData;
private:
	static SceneCollision *_instance;
#endif
};

};

#endif