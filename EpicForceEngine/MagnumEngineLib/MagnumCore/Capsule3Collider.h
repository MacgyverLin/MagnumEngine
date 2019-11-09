///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Capsule3Collider_h_
#define _Capsule3Collider_h_

#include "Stage.h"
#include "Physics3.h"
#include "CapsuleShape3.h"
using namespace Magnum;

namespace Magnum
{

/**
* Capsule3Collider Component.
* Capsule3Collider Component is a Capsule3 RigidBody Component.
* @see RigidBody
*/
class Capsule3Collider : public Physics3::RigidBody
{
public:
////////////////////////////////////////////////////////////////
public:
	/**
	* Capsule3Collider Constructor.
	* To Construct the Capsule3Collider for the owner.
	* @param owner_, the Component::Owner which owns this component.
	*/
	Capsule3Collider(Component::Owner &owner_);

	/**
	* Capsule3Collider Destructor.
	* To Destruct Capsule3Collider and remove from its owner.
	*/
	~Capsule3Collider();

	DECLARE_COMPONENT(Capsule3Collider, Physics3::RigidBody, false)
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

	/**
	* Set the Height of the Capsule
	* @param value_, float, the Height of the Capsule
	*/
	/**
	* Get the Height of the Capsule
	* @return the Height of the Capsule
	*/
	PROPERTY(float, Height);
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
	CapsuleShape3 capsuleShape3;
};

};

#endif
