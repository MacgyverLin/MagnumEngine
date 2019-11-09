///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _SphereCollider_h_
#define _SphereCollider_h_

#include "Stage.h"
#include "Selection3.h"
using namespace Magnum;

namespace Magnum
{

/**
* CapsuleBound Component.
* CapsuleBound Component is a Capsule RigidBody Component.
* @see Selection3::Bound
*/
class CapsuleBound : public Selection3::Bound
{
public:
	////////////////////////////////////////////////////////////////
	/**
	* CapsuleBound Constructor.
	* To Construct the CapsuleBound for the owner.
	* @param owner_, the Component::Owner which owns this component.
	*/
	CapsuleBound(Component::Owner &owner_);

	/**
	* CapsuleBound Destructor.
	* To Destruct CapsuleBound and remove from its owner.
	*/
	~CapsuleBound();

	////////////////////////////////////////////////////////////////
	DECLARE_COMPONENT(CapsuleBound, Selection3::Bound, false)

	/**
	* Set the Radius of the Capsule
	* @param value_, float, the Radius of the Capsule
	*/
	/**
	* Get the Radius of the Capsule
	* @return the Radius of the Capsule
	*/
	PROPERTY(float	, Radius);

	/**
	* Set the Height of the Capsule
	* @param value_, float, the Height of the Capsule
	*/
	/**
	* Get the Height of the Capsule
	* @return the Height of the Capsule
	*/
	PROPERTY(Vector3, Axis);
	////////////////////////////////////////////////////////////////
public:
	/**
	* Do Ray Casting for a ray by specifying starting point and direction
	* @param from, Vector3, the starting point of the ray
	* @param dir, Vector3, the direction of the ray
	*/
	virtual bool rayCast(const Vector3 &from, const Vector3 &dir);

	/**
	* Do Sphere Casting for a sphere by specifying starting point and direction
	* @param from, Vector3, the starting point of the sphere
	* @param radius, float, the radius of the sphere
	* @param dir, Vector3, the direction of the sphere
	*/
	virtual bool sphereCast(const Vector3 &from, float radius, const Vector3 &dir);
protected:
private:
///////////////////////////////////////////////////////////////////////////////////
public:
protected:
private:
};

};

#endif
