///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _HeightFieldCollider_h_
#define _HeightFieldCollider_h_

#include "Stage.h"
#include "Physics3.h"
#include "HeightFieldShape3.h"
using namespace Magnum;

namespace Magnum
{

/**
* HeightFieldCollider Component.
* HeightFieldCollider Component is a HeightField RigidBody Component.
* @see RigidBody
*/
class HeightFieldCollider : public Physics3::RigidBody
{
public:
////////////////////////////////////////////////////////////////
public:
	/**
	* HeightFieldCollider Constructor.
	* To Construct the HeightFieldCollider for the owner.
	* @param owner_, the Component::Owner which owns this component.
	*/
	HeightFieldCollider(Component::Owner &owner_);

	/**
	* HeightFieldCollider Destructor.
	* To Destruct HeightFieldCollider and remove from its owner.
	*/
	~HeightFieldCollider();

	DECLARE_COMPONENT(HeightFieldCollider, Physics3::RigidBody, false)
public:
	Physics3::RigidBody::Type	type;					/**< Static Physics3::RigidBody::Type	type		*/ 
	Physics3::Material			material;				/**< Static Physics3::Material			material	*/ 
	Physics3::CollisionFilter	collisionFilter;		/**< Static Physics3::CollisionFilter	collisionFilter	*/ 
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
	HeightFieldShape3 heightFieldShape3;
};

};

#endif
