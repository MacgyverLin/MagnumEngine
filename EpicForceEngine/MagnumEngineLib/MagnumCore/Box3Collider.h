///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Box3Collider_h_
#define _Box3Collider_h_

#include "Stage.h"
#include "Physics3.h"
#include "BoxShape3.h"
using namespace Magnum;

namespace Magnum
{

/**
* Box3Collider Component.
* Box3Collider Component is a Box3 RigidBody Component.
* @see RigidBody
*/
class Box3Collider : public Physics3::RigidBody
{
public:
////////////////////////////////////////////////////////////////
public:
	/**
	* Box3Collider Constructor.
	* To Construct the Box3Collider for the owner.
	* @param owner_, the Component::Owner which owns this component.
	*/
	Box3Collider(Component::Owner &owner_);

	/**
	* Box3Collider Destructor.
	* To Destruct Box3Collider and remove from its owner.
	*/
	~Box3Collider();

	DECLARE_COMPONENT(Box3Collider, Physics3::RigidBody, false)
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
	* Set the Extent of Box3 of the Collider
	* @param value_, Vector3 the Extent of the Box3
	*/
	/**
	* Get the Extent of Box3 of the Collider
	* @return the Extent as Vector3
	*/
	PROPERTY(Vector3, Extent);
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
	BoxShape3 boxShape3;
};

};

#endif
