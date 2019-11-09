///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
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

using namespace Magnum;

#define SMOOTHER_WII_COLLISION

namespace Magnum
{

/**
* @brief This is the sub class for Scene Collision Object
*/
class SceneCollision : public Collision
{
public:
	class Resource;
	class ResourceImporter;

	class CastInfo
	{
	public:
		/**
		* CastInfo Constructor.
		* To Construct the CastInfo.
		*/
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
		bool collided;							/**< indicated collided occurs */ 
		Vector3 inputPosition;					/**< the position of the test point */ 
		Vector3 inputDistance;					/**< inputDistance */ 
		float inputRadius;						/**< the radius of the testing sphere */ 

		Vector3 outputPosition;					/**< the contact Position */ 
		Vector3 *outputNormal;					/**< the contact Normal */ 
		bool outputStartOut;					 
		bool outputAllSolid;					/**< in side wall */ 
		float outputFraction;					/**< the fraction of the ray intersection */ 
		int outputID;							/**< outputID */ 

		Vector3 contactPoint;					/**< the contact Position */ 
		Vector3 contactNormal;					/**< the contact Normal */ 
		float penetrationDepth;					/**< the penetration depth */ 
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
	/////////////////////////////////////////////////////////////////////////////////////////
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
	/////////////////////////////////////////////////////////////////////////////////////////
	public:
	protected:
	private:
		Vector<HeightField> heightFields;
	};

	//////////////////////////////////////////////////////////////////////////////////////////
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
	/////////////////////////////////////////////////////////////////////////////////////////
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
	/////////////////////////////////////////////////////////////////////////////////////////
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
	/**
	* SceneCollision Constructor.
	* To Construct the SceneCollision
	*/
	SceneCollision();

	/**
	* SceneCollision Destructor.
	* To Destruct SceneCollision
	*/
	~SceneCollision();

	static SceneCollision &instance();

	/**
	* @brief This function construct the scene collision
	* @param name_, const char *, the name of the resource
	*/ 
	bool construct(const char *name_);

	/**
	* @brief This function append the scene collision
	* @param name_, const char *, the name of the resource
	*/ 
	bool append(const char *name_);

	/**
	* @brief This function destruct the scene collision
	*/ 
	void destruct();

	/**
	* @brief This function test if a point intersect with any brush or height field in this scene
	* @param point_, Vector3, the time elapse.
	*/
	bool test(Vector3 &point_);

	/**
	* @brief This function test if a point intersect with any brush or height field in this scene
	* @param castInfo_, SceneCollision::CastInfo, the cast info.
	*/
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