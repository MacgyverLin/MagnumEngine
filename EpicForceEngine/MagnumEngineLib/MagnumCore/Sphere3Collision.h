///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Sphere3Collision_h_
#define _Sphere3Collision_h_

#include "Collision.h"

/*
			sphere capsule octtree
 sphere       o       o     todo
 capsule      o       x      x
 octtree     todo     x     n/a
*/

namespace Magnum
{

/**
* @brief This is the sub class for spherical Collision Object
*
* The Position/Rotation Collision Sphere can be retrieve by getTransform(). 
* Its radius is set by Sphere3Collision::setRadius
* Scaling of the Transform is not supported.
*
*/
class Sphere3Collision : public Collision
{
friend class Collision;
public:
	/**
	* Sphere3Collision Constructor.
	* To Construct the Sphere3Collision
	* @param radius_, float, the radius of the Sphere
	*/
	Sphere3Collision(const float &radius_ = 1);

	/**
	* Sphere3Collision Destructor.
	* To Destruct Sphere3Collision
	*/
	virtual ~Sphere3Collision();

	/**
	* @brief This function set the radius of the sphere
	* @param radius_, float, the radius of the Sphere
	*/ 
	// setter
	void setRadius(const float &radius_);

	/**
	* @brief This function return the radius of the sphere
	* @return float the radius of the Sphere
	*/ 
	// getter
	float getRadius() const;

	/**
	* @brief This is a virtual function. The function checks if a point, defined in world space, is inside the collision shape
	*
	* @param world_point the coordinates, defined in world space, to be checked against the collider
	*
	* @return true  if world_point is inside collision
	*         false if world_point is not inside collision
	*/ 
	virtual bool isInside(const Vector3 &world_point);
protected:
	/**
	* @brief This function test for collision in general, if other_ is sphere it will call testWithSphere3. if the other_ is Scene, it will call  
	* @param dt, the time elapse.
	* @param other_, the Other collision object.
	* @param info_, if collision is detected, the ContactInfo of the collision is return here.
	*/
	virtual bool test(float dt, Collision *other_, ContactInfo &info_);

	/**
	* @brief This function test for collision with Sphere3
	* @param dt, the time elapse.
	* @param other_, the Other collision object.
	* @param info_, if collision is detected, the ContactInfo of the collision is return here.
	*/
	bool testWithSphere3(float dt, Collision *other_, ContactInfo &info_);

	/**
	* @brief This function test for collision with Scene
	* @param dt, the time elapse.
	* @param other_, the Other collision object.
	* @param info_, if collision is detected, the ContactInfo of the collision is return here.
	*/
	bool testWithScene(float dt, Collision *other_, ContactInfo &info_);
private:
	float radius; ///< radius
};

};

#endif