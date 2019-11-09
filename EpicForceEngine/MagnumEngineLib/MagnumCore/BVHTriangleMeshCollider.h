///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _BVHTriangleMeshCollider_h_
#define _BVHTriangleMeshCollider_h_

#include "Stage.h"
#include "Physics3.h"
#include "BVHTriangleMeshShape3.h"
#include "ResourcePath.h"
using namespace Magnum;

namespace Magnum
{

/**
* BVHTriangleMeshCollider Component.
* BVHTriangleMeshCollider Component is a Hierachical Triangle Mesh RigidBody Component.
* @see RigidBody
*/
class BVHTriangleMeshCollider : public Physics3::RigidBody
{
public:
////////////////////////////////////////////////////////////////
public:
	/**
	* BVHTriangleMeshCollider Constructor.
	* To Construct the BVHTriangleMeshCollider for the owner.
	* @param owner_, the Component::Owner which owns this component.
	*/
	BVHTriangleMeshCollider(Component::Owner &owner_);

	/**
	* BVHTriangleMeshCollider Destructor.
	* To Destruct BVHTriangleMeshCollider and remove from its owner.
	*/
	~BVHTriangleMeshCollider();

	DECLARE_COMPONENT(BVHTriangleMeshCollider, Physics3::RigidBody, false)
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
	* Set the File Path of BVHTriangleMesh
	* @param value_, String the File Path of BVHTriangleMesh
	*/
	/**
	* Get the File Path of BVHTriangleMesh
	* @return the File Path of BVHTriangleMesh
	*/
	PROPERTY(ResourcePath, ColliderPath);
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
	BVHTriangleMeshShape3 bvhTriangleMeshShape3;
};

};

#endif
