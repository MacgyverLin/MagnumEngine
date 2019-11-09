///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Shape3_h_
#define _Shape3_h_

#include "Stage.h"
#include "Component.h"
#include "AABB3.h"
using namespace Magnum;

namespace Magnum
{

/**
* Shape3.
* This is the base class for all Shapes.
*/
class Shape3
{
public:
	enum Type
	{
		// Is it a moving object?
		//		|	
		//		|	
		//		+-----Can it be approximated by a single primitive, such as box, sphere, capsule, cone, cylinder?
		//		|		+----btBoxShape, btSphereShape, btCapsuleShape, btCylinderShape, btConeShape
		//		|	    |
		//		|       +-----Can it be approximated by a convex hull of a triangle mesh?
		//		|				+----btConvexHullShape
		//		|				|	
		//		|				+----Can it be approximated using multiple primitives, such as box, sphere etc?
		//		|						+----btCompoundShape
		//		|						|	
		//		|						+----btGimpactTriangleMeshShape
		//		|
		//		+-----Is it a 2D heightfield?
		//		|		+----btHeightfieldTerrainShape
		//		|	    |
		//		|       +-----Are there shared scaled instances?
		//		|				+----btScaledBvhTriangleMeshShape
		//		|				|	
		//		|				+----btBvhTriangleMeshShape
		BOX								= 0,		/**< a BOX Shape */ 
		SPHERE							= 1,		/**< a SPHERE Shape */ 
		CAPSULE							= 2,		/**< a CAPSULE Shape */ 
		CYLINDER						= 3,		/**< a CYLINDER Shape */ 
		CONE							= 4,		/**< a CONE Shape */ 
		CONVEXHULL						= 5,		/**< a CONVEXHULL Shape */ 
		COMPOSITE						= 6,		/**< a COMPOSITE Shape */ 
		CONCAVETRIANGLEMESH				= 7,		/**< a CONCAVETRIANGLEMESH Shape */ 
		HEIGHT_FIELD					= 8,		/**< a HEIGHT_FIELD Shape */ 
		BVH_TRIANGLE_MESH_INSTANCE		= 9,		/**< a BVH_TRIANGLE_MESH_INSTANCE Shape */ 
		BVH_TRIANGLE_MESH				= 10,		/**< a BVH_TRIANGLE_MESH Shape */ 
		NUM_TYPES
	};

	/**
	* Shape3 Constructor.
	* @param type_, specify the type of the shape
	* To Construct the Shape3
	*/
	Shape3(Shape3::Type type_);

	/**
	* Shape3 Destructor.
	* To Destruct Shape3
	*/
	virtual ~Shape3();

	/**
	* Get the type of the Shape.
	* @return Shape3::Type, the type of the Shape.
	*/
	Shape3::Type getType() const;

	//virtual int32 GetChildCount() const = 0;
	//virtual bool TestPoint(const b2Transform& xf, const b2Vec2& p) const = 0;
	//virtual bool RayCast(b2RayCastOutput* output, const b2RayCastInput& input, const b2Transform& transform, int32 childIndex) const = 0;
	//virtual void ComputeAABB(b2AABB* aabb, const b2Transform& xf, int32 childIndex) const = 0;
	//virtual void ComputeMass(b2MassData* massData, float32 density) const = 0;
	/**
	* Get a constant pointer to a child shape of this shape.
	* @param i, the index to the child shape
	* @return Shape3*, child shape at this index
	*/
	virtual const Shape3 *getChild(int i) const;

	/**
	* Get a pointer to a child shape of this shape.
	* @param i, the index to the child shape
	* @return Shape3*, child shape at this index
	*/
	virtual Shape3 *getChild(int i);

	/**
	* Get the Number of Child Shapes of this Shape;
	* @return int, Number of Child Shapes of this Shape
	*/
	virtual int getNumChildren() const;
	
	/**
	* Get the Bounding Box of this Shape;
	* @return AABB3, the Bounding Box of this Shape;
	*/
	const AABB3 &getBoundingBox() const;

	/**
	* Get the Volume of this Shape;
	* @return float, the Volume of this Shape;
	*/
	float getVolume() const;

	/**
	* To calculate the mass and moment of inertia according to the shape and density.
	* Being a pure virtual member, all subclass should implement this function.
	* @param density, the density of the shape
	* @param mass, the result of the mass of the shape is returned here
	* @param localInertia, the result of the moment of inertia of the shape is returned here
	*/
	virtual void getMassProp(float density, float &mass, Vector3 &localInertia) const = 0;

	void *getHandle() const;
protected:
	AABB3	boundingBox;
	float	volume;

	void	*handle;
private:
	Type	type;
};

/**
* ConvexShape3.
* This is the base class for all Convex Shapes.
* @see Shape3
*/
class ConvexShape3 : public Shape3
{
public:
	/**
	* ConvexShape3 Constructor.
	* @param type_, specify the type of the shape
	* To Construct the ConvexShape3
	*/
	ConvexShape3(Shape3::Type type_)
	: Shape3(type_)
	{
	}

	/**
	* ConvexShape3 Destructor.
	* To Destruct ConvexShape3
	*/
	~ConvexShape3()
	{
	}
protected:
private:
/////////////////////////////////////////////////////
public:
protected:
private:
};

/**
* ConcaveShape3.
* This is the base class for all Concave Shapes.
* @see Shape3
*/
class ConcaveShape3 : public Shape3
{
public:
	/**
	* ConcaveShape3 Constructor.
	* @param type_, specify the type of the shape
	* To Construct the ConcaveShape3
	*/
	ConcaveShape3(Shape3::Type type_)
	: Shape3(type_)
	{
	}

	/**
	* ConcaveShape3 Destructor.
	* To Destruct ConcaveShape3
	*/
	~ConcaveShape3()
	{
	}
protected:
private:
/////////////////////////////////////////////////////
public:
protected:
private:
};

};

#endif