///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _BoxShape3_h_
#define _BoxShape3_h_

#include "Stage.h"
#include "Vector3.h"
#include "AABB3.h"
#include "Shape3.h"
using namespace Magnum;

namespace Magnum
{

/**
* BoxShape3.
* This class define a 3D Box Shape.
* @see ConvexShape3
*/
class BoxShape3 : public ConvexShape3
{
public:
	/**
	* BoxShape3 Constructor.
	* To Construct the BoxShape3 for the owner.
	*/
	BoxShape3();

	/**
	* BoxShape3 Destructor.
	* To Destruct BoxShape3 and remove from its owner.
	*/
	~BoxShape3();

	/**
	* construct the BoxShape3.
	* @param halfExtent_, the extent of the box
	* @return true if success, false if fail.
	*/
	bool construct(const Vector3 &halfExtent_);

	/**
	* destruct BoxShape3 and release memory its used
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
};

};

#endif