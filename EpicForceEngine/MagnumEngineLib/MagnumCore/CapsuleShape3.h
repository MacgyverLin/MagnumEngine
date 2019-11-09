///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _CapsuleShape3_h_
#define _CapsuleShape3_h_

#include "Stage.h"
#include "Vector3.h"
#include "Shape3.h"
using namespace Magnum;

namespace Magnum
{

/**
* CapsuleShape3.
* This class define a Capsule Shape.
* @see ConvexShape3
*/
class CapsuleShape3 : public ConvexShape3
{
public:
	enum AxisDirection
	{
		X_AXIS,		/**< Height Align to XAxis.		*/ 
		Y_AXIS,		/**< Height Align to YAxis.		*/ 
		Z_AXIS		/**< Height Align to ZAxis.		*/ 
	};

	/**
	* CapsuleShape3 Constructor.
	* To Construct the CapsuleShape3
	*/
	CapsuleShape3();

	/**
	* CapsuleShape3 Destructor.
	* To Destruct CapsuleShape3
	*/
	~CapsuleShape3(); 

	/**
	* construct the CapsuleShape3.
	* @param axisDir_, the major axis of the capsule
	* @param radius_, the radius of the capsule
	* @param height_, the height of the capsule
	* @return true if success, false if fail.
	*/
	bool construct(CapsuleShape3::AxisDirection axisDir_, float radius_, float height_);

	/**
	* destruct CapsuleShape3 and release memory its used
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