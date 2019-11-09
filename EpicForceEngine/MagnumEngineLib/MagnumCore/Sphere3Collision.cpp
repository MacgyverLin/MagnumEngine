///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Sphere3Collision.h"
#include "SceneCollision.h"
using namespace Magnum;

/**
* @brief The constructor
*
* @param radius_ The radius of this Sphere Collider, default value 1
*/ 
Sphere3Collision::Sphere3Collision(const float &radius_) 
: Collision(CT_SPHERE3)
, radius(radius_)
{
}

/**
* @brief The destructor
*
*/ 
Sphere3Collision::~Sphere3Collision()
{
}

// setter
/**
* @brief Set the Radius of this Sphere Collider
*
* @param radius_ The radius of this Sphere Collider
*/ 
void Sphere3Collision::setRadius(const float &radius_)
{
	radius = radius_;
}

// getter
/**
* @brief get the Radius of this Sphere Collider
*
* @return float The radius of this Sphere Collider
*/ 
float Sphere3Collision::getRadius() const
{
	return radius;
}

/**
* @brief This is a pure virtual function. The function checks if a point, defined in world space, is inside the collision shape
*
* @param world_point the coordinates, defined in world space, to be checked against the collider
*
* @return true  if world_point is inside collision
*         false if world_point is not inside collision
*/ 
bool Sphere3Collision::isInside(const Vector3 &world_point)
{
	return (getPosition() - world_point).SquaredLength() < radius;
}

/**
* @brief The function is a core function for calculate collision
*
* This function implements the collision detection with all possible type of other_
* enummerated by Collision::Type
*
* @param other the other collision instance to be checked with
* @param info_.collided set by this function, true if collision occurs, false other wise
* @param info_.contactPoint set by this function, the calculated Contact Point of the Collided surface 
* @param info_.contactNormal set by this function, the calculated Contact Normal of the Collided surface 
* @param info_.penetrationDepth set by this function, the depth in which this instance penetrate with the other.
*
* @return true  if collision detection is calculated
*         false if collision detection is not calculated, i.e. no implemnetation
*/ 
bool Sphere3Collision::test(float dt, Collision *other_, ContactInfo &info_)
{
	switch(other_->getType())
	{
		case CT_SPHERE3:
			return testWithSphere3(dt, other_, info_);

		case CT_SCENE:
			return testWithScene(dt, other_, info_);
		
		default:
			return false;
	};
}

/**
* @brief The function is a core function for calculate collision
*
* This function implements the collision detection with SphereCollision
* enummerated by Collision::Type
*
* @param other the other collision instance to be checked with
* @param info_.collided set by this function, true if collision occurs, false other wise
* @param info_.contactPoint set by this function, the calculated Contact Point of the Collided surface 
* @param info_.contactNormal set by this function, the calculated Contact Normal of the Collided surface 
* @param info_.penetrationDepth set by this function, the depth in which this instance penetrate with the other.
*
* @return true  if collision detection is calculated
*         false if collision detection is not calculated, i.e. no implemnetation
*/ 
bool Sphere3Collision::testWithSphere3(float dt, Collision *other_, ContactInfo &info_)
{
	const Sphere3Collision *sph0 = this;
	const Sphere3Collision *sph1 = (const Sphere3Collision *)other_;

	Vector3 center_diff		= sph0->getPosition() - sph1->getPosition();
	float radiusSum         = sph0->getRadius()   + sph1->getRadius();
	float center_dist_sqr   = center_diff.SquaredLength();

	info_.collided = center_dist_sqr < radiusSum * radiusSum;
	if(info_.collided)
	{
		float center_dist		= center_diff.Normalize();
		info_.contactNormal		= center_diff;
		info_.penetrationDepth	= (radiusSum - center_dist) * 0.5f;
		info_.contactPoint		= sph0->getPosition() - 
								  info_.contactNormal * (sph0->getRadius() - info_.penetrationDepth);
		info_.resolvePosition0	= sph0->getPosition() + info_.contactNormal * info_.penetrationDepth;
		info_.resolvePosition1	= sph1->getPosition() - info_.contactNormal * info_.penetrationDepth;
	}
	
	return true;
}

/**
* @brief The function is a core function for calculate collision
*
* This function implements the collision detection with SceneCollision
* enummerated by Collision::Type
*
* @param other the other collision instance to be checked with
* @param info_.collided set by this function, true if collision occurs, false other wise
* @param info_.contactPoint set by this function, the calculated Contact Point of the Collided surface 
* @param info_.contactNormal set by this function, the calculated Contact Normal of the Collided surface 
* @param info_.penetrationDepth set by this function, the depth in which this instance penetrate with the other.
*
* @return true  if collision detection is calculated
*         false if collision detection is not calculated, i.e. no implemnetation
*/ 
bool Sphere3Collision::testWithScene(float dt, Collision *other_, ContactInfo &info_)
{
	const Sphere3Collision *sph0	  = this;
	SceneCollision   *sce			  = (SceneCollision *)other_;

	SceneCollision::CastInfo castInfo;
	castInfo.inputPosition		= sph0->getPosition();
	castInfo.inputDistance		= sph0->getVelocity() * dt;
	castInfo.inputRadius		= sph0->getRadius();
	
	sce->testSphere(castInfo);
	
	info_.resolvePosition0	= castInfo.outputPosition;
	info_.resolvePosition1	= sce->getPosition();
	info_.collided			= castInfo.collided;
	info_.contactPoint		= castInfo.contactPoint;
	info_.contactNormal		= castInfo.contactNormal;
	info_.penetrationDepth	= castInfo.penetrationDepth;
	
	return true;
}