///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _RaySphereCast_h_
#define _RaySphereCast_h_

#include "Stage.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include "Physics3.h"
#include "Vector3.h"
using namespace Magnum;

namespace Magnum
{

/**
* ClosestRayCastCB.
* ClosestRayCastCB defines the call back structure used for ClosestRayCastCB.
* ClosestRayCastCB returns the closest intersection point of the raycasting
*/
struct ClosestRayCastCB : public btCollisionWorld::RayResultCallback
{
	/**
	* ClosestRayCastCB Constructor.
	* To Construct the ClosestRayCastCB
	* @param result_, Physics3::RayCastResult, the result of ray casting is return in this parameter
	* @param rayFromWorld_, Vector3, the ray starting point
	* @param rayToWorld_, Vector3, the ray starting point
	*/
	ClosestRayCastCB(Physics3::RayCastResult &result_,
					 const Vector3 &rayFromWorld_, const Vector3 &rayToWorld_)
	: result(result_)
	{
		result.rayFromWorld = rayFromWorld_;
		result.rayToWorld   = rayToWorld_;
	}

	/**
	* The callback function for Raycaster.
	* This function is called by the Physics3 Service when it detect the ray hit certain Shape in the physics world
	* @param rayResult, Physics3::RayCastResult, the result of ray casting is return in this parameter
	* @param normalInWorldSpace, if true the normal is return in world space, otherwise return in object local space
	* @param float, the fraction of the ray closest intersection. 
	*/
	virtual	btScalar addSingleResult(btCollisionWorld::LocalRayResult &rayResult, bool normalInWorldSpace)
	{
		//caller already does the filter on the m_closestHitFraction
		btAssert(rayResult.m_hitFraction <= m_closestHitFraction);
		
		m_closestHitFraction	= rayResult.m_hitFraction;
		m_collisionObject		= rayResult.m_collisionObject;
		
		btVector3 normal;
		if(normalInWorldSpace)
		{
			normal = rayResult.m_hitNormalLocal;
		} 
		else
		{
			normal = m_collisionObject->getWorldTransform().getBasis()*rayResult.m_hitNormalLocal;
		}
		
		// m_hitPointWorld.setInterpolate3(m_rayFromWorld, m_rayToWorld, rayResult.m_hitFraction);
		result.hasHit						= true;
		result.hitFractions.push()			= rayResult.m_hitFraction;
		result.hitNormalWorlds.push()		= CONST_CAST_VECTOR3(normal);
		result.hitPointWorlds.push()		= result.rayFromWorld * (1.0f-rayResult.m_hitFraction) + 
											  result.rayToWorld   * rayResult.m_hitFraction;
		result.hitCollisionObjects.push()	= rayResult.m_collisionObject->getUserPointer();

		return rayResult.m_hitFraction;
	}

	Physics3::RayCastResult &result;
};

/**
* ClosestConvexCastCB.
* ClosestConvexCastCB defines the call back structure used for ClosestConvexCastCB.
* ClosestConvexCastCB returns the closest intersection point of the casting a convex shape in thw physics world
*/
struct ClosestConvexCastCB : public btCollisionWorld::ConvexResultCallback
{
	/**
	* ClosestConvexCastCB Constructor.
	* To Construct the ClosestConvexCastCB
	* @param result_, Physics3::RayCastResult, the result of convex shape casting is return in this parameter
	* @param convexFromWorld_, Vector3, the ConvexCast starting point
	* @param convexToWorld_, Vector3, the ConvexCast starting point
	*/
	ClosestConvexCastCB(Physics3::ConvexCastResult &result_, 
					    const Vector3 &convexFromWorld_, const Vector3 &convexToWorld_)
	: result(result_)
	{
		result.convexFromWorld = convexFromWorld_;
		result.convexToWorld   = convexToWorld_;
	}

	/**
	* The callback function for ConvexCaster.
	* This function is called by the Physics3 Service when it detect an intesection between convex casting and certain Shape in the physics world
	* @param convexResult, Physics3::LocalConvexResult, the result of convex casting is return in this parameter
	* @param normalInWorldSpace, if true the normal is return in world space, otherwise return in object local space
	* @param float, the fraction of the ray closest intersection. 
	*/
	virtual	btScalar addSingleResult(btCollisionWorld::LocalConvexResult &convexResult, bool normalInWorldSpace)
	{
		// caller already does the filter on the m_closestHitFraction
		btAssert(convexResult.m_hitFraction <= m_closestHitFraction);
					
		m_closestHitFraction = convexResult.m_hitFraction * 0.99f;

		btVector3 normal;
		if(normalInWorldSpace)
		{
			normal = convexResult.m_hitNormalLocal;
		}
		else
		{
			normal = convexResult.m_hitCollisionObject->getWorldTransform().getBasis()*convexResult.m_hitNormalLocal;
		}

		result.hasHit						= true;
		result.hitFractions.push()			= convexResult.m_hitFraction * 0.99f;
		result.hitNormalWorlds.push()		= CONST_CAST_VECTOR3(normal);
		result.hitPointWorlds.push()		= result.convexFromWorld * (1.0f-convexResult.m_hitFraction * 0.99f) + 
											  result.convexToWorld   * convexResult.m_hitFraction * 0.99f;
		//result.hitPointWorlds.push()		= CONST_CAST_VECTOR3(convexResult.m_hitPointLocal);
		result.hitCollisionObjects.push()	= convexResult.m_hitCollisionObject->getUserPointer();

		return convexResult.m_hitFraction;
	}

	Physics3::ConvexCastResult &result;
};

////////////////////////////////////////////////////////////////////////////////////////////////
/**
* AllHitsRayCastCB.
* AllHitsRayCastCB defines the call back structure used for AllHitsRayCastCB.
* AllHitsRayCastCB returns the all intersection point of the raycasting
*/
struct AllHitsRayCastCB : public btCollisionWorld::RayResultCallback
{
	/**
	* AllHitsRayCastCB Constructor.
	* To Construct the AllHitsRayCastCB
	* @param result_, Physics3::RayCastResult, the result of ray casting casting is return in this parameter
	* @param rayFromWorld_, Vector3, the Ray cast starting point
	* @param rayToWorld_, Vector3, the Ray cast starting point
	*/
	AllHitsRayCastCB(Physics3::RayCastResult &result_,
					 const Vector3 &rayFromWorld_, const Vector3 &rayToWorld_)
	: result(result_)
	{
		result.rayFromWorld = rayFromWorld_;
		result.rayToWorld   = rayToWorld_;
	}

	/**
	* The callback function for AllHitsRayCastCB.
	* This function is called by the Physics3 Service when it detect an intesection between ray and certain Shape in the physics world
	* @param convexResult, Physics3::LocalConvexResult, the result of convex casting is return in this parameter
	* @param normalInWorldSpace, if true the normal is return in world space, otherwise return in object local space
	* @param float, the fraction of the ray closest intersection. 
	*/
	virtual	btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace)
	{
		m_collisionObject					= rayResult.m_collisionObject;

		btVector3 hitNormalWorld;
		if (normalInWorldSpace)
		{
			hitNormalWorld = rayResult.m_hitNormalLocal;
		}
		else
		{
			///need to transform normal into worldspace
			hitNormalWorld = m_collisionObject->getWorldTransform().getBasis()*rayResult.m_hitNormalLocal;
		}

		result.hasHit						= true;
		result.hitFractions.push()			= rayResult.m_hitFraction;
		result.hitNormalWorlds.push()		= CONST_CAST_VECTOR3(hitNormalWorld);
		result.hitPointWorlds.push()		= result.rayFromWorld * (1.0f-rayResult.m_hitFraction) + 
											  result.rayToWorld   * rayResult.m_hitFraction;
		result.hitCollisionObjects.push()	= rayResult.m_collisionObject->getUserPointer();

		return m_closestHitFraction;
	}

	Physics3::RayCastResult &result;
};

/**
* AllHitsConvexCastCB.
* AllHitsConvexCastCB defines the call back structure used for AllHitsConvexCastCB.
* AllHitsConvexCastCB returns the all intersection points of the casting a convex shape in thw physics world
*/
struct AllHitsConvexCastCB : public btCollisionWorld::ConvexResultCallback
{
	/**
	* AllHitsConvexCastCB Constructor.
	* To Construct the AllHitsConvexCastCB
	* @param result_, Physics3::RayCastResult, the result of convex shape casting is return in this parameter
	* @param convexFromWorld_, Vector3, the ConvexCast starting point
	* @param convexToWorld_, Vector3, the ConvexCast starting point
	*/
	AllHitsConvexCastCB(Physics3::ConvexCastResult &result_,
					    const Vector3 &convexFromWorld_, const Vector3 &convexToWorld_)
	: result(result_)
	{
		result.convexFromWorld = convexFromWorld_;
		result.convexToWorld   = convexToWorld_;
	}

	/**
	* The callback function for AllHitsConvexCastCB.
	* This function is called by the Physics3 Service when it detect an intesection between convex casting and certain Shape in the physics world
	* @param convexResult, Physics3::LocalConvexResult, the result of convex casting is return in this parameter
	* @param normalInWorldSpace, if true the normal is return in world space, otherwise return in object local space
	* @param float, the fraction of the ray closest intersection. 
	*/
	virtual	btScalar addSingleResult(btCollisionWorld::LocalConvexResult &convexResult, bool normalInWorldSpace)
	{
		btVector3 hitNormalWorld;
		if (normalInWorldSpace)
		{
			hitNormalWorld = convexResult.m_hitNormalLocal;
		}
		else
		{
			///need to transform normal into worldspace
			hitNormalWorld = convexResult.m_hitCollisionObject->getWorldTransform().getBasis()*convexResult.m_hitNormalLocal;
		}

		result.hasHit						= true;
		result.hitFractions.push()			= convexResult.m_hitFraction;
		result.hitNormalWorlds.push()		= CONST_CAST_VECTOR3(hitNormalWorld);
		result.hitPointWorlds.push()		= result.convexFromWorld * (1.0f-convexResult.m_hitFraction) + 
											  result.convexToWorld   * convexResult.m_hitFraction;
		result.hitCollisionObjects.push()	= convexResult.m_hitCollisionObject->getUserPointer();

		return m_closestHitFraction;
	}

	Physics3::ConvexCastResult &result;
};

};

#endif
