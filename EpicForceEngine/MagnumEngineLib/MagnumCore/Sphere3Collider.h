///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Sphere3Collider_h_
#define _Sphere3Collider_h_

#include "Stage.h"
#include "Physics3.h"
#include "SphereShape3.h"
using namespace Magnum;

namespace Magnum
{

/**
* Sphere3Collider Component.
* Sphere3Collider Component is a HeightField RigidBody Component.
* @see RigidBody
*/
class Sphere3Collider : public Physics3::RigidBody
{
public:
////////////////////////////////////////////////////////////////
public:
	/**
	* Sphere3Collider Constructor.
	* To Construct the Sphere3Collider for the owner.
	* @param owner_, the Component::Owner which owns this component.
	*/
	Sphere3Collider(Component::Owner &owner_);

	/**
	* Sphere3Collider Destructor.
	* To Destruct Sphere3Collider and remove from its owner.
	*/
	~Sphere3Collider();

	DECLARE_COMPONENT(Sphere3Collider, Physics3::RigidBody, false)
public:
	Physics3::RigidBody::Type	type;					/**< Static Physics3::RigidBody::Type	type		*/ 
	Physics3::Material			material;				/**< Static Physics3::Material			material	*/ 
	Physics3::CollisionFilter	collisionFilter;		/**< Static Physics3::CollisionFilter	collisionFilter	*/ 

	/**
	* Set if the Collider is Static RigidBody.
	* @param value_, true if Static else Dynamic
	*/
	/**
	* check if the Collider is Static RigidBody.
	* @return true if is Static, else Dynamic.
	*/
	PROPERTY(bool, Static);

	/**
	* Set the Radius of the Capsule
	* @param value_, float, the Radius of the Capsule
	*/
	/**
	* Get the Radius of the Capsule
	* @return the Radius of the Capsule
	*/
	PROPERTY(float, Radius);
////////////////////////////////////////////////////////////////
public:
protected:
private:
	/**
	* Handle Construct Event of the Component
	* @return true if construction is success, return false if fail
	*/
	virtual bool onConstruct();

	/**
	* Handle Start Event of the Component
	*/
	virtual void onStart();

	/**
	* Handle Update Event of the Component
	* @param delta elapse of the game cycle
	*/
	virtual void onUpdate(float dt);

	/**
	* Handle Pause Event of the Component
	*/
	virtual void onPause();

	/**
	* Handle Resume Event of the Component
	*/
	virtual void onResume();

	/**
	* Handle Stop Event of the Component
	*/
	virtual void onStop();

	/**
	* Handle Destruct Event of the Component
	*/
	virtual void onDestruct();

	/**
	* Handle Debuger Rendering Event of the Component
	*/
	virtual void onDebugRender(IComponentDebugRenderer &debugRenderer);
///////////////////////////////////////////////////////////////////////////////////
public:
protected:
private:
	SphereShape3 sphereShape3;
};

};

#endif
