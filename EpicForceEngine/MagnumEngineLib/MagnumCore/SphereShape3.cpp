///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "SphereShape3.h"
#include "Physics3.h"
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
using namespace Magnum;

SphereShape3::SphereShape3()
: ConvexShape3(Shape3::SPHERE)
{
}

SphereShape3::~SphereShape3()
{
	assert(handle==0);
}

bool SphereShape3::construct(float radius_)
{
	assert(handle==0);

	btSphereShape *shape = new btSphereShape(radius_);
	handle = shape;

	btVector3 min, max;
	btTransform transform;
	transform.setIdentity();
	shape->getAabb(transform, min, max);

	boundingBox.Min = Vector3(min.x(), min.y(), min.z());
	boundingBox.Max = Vector3(max.x(), max.y(), max.z());
	Vector3 size(boundingBox.Max - boundingBox.Min);

	volume = 4.0/3.0 * Math::ONE_PI * radius_ * radius_ * radius_;

	return handle!=0;
}

void SphereShape3::destruct()
{
	if(handle)
	{
		delete ((btSphereShape *)handle);
		handle = 0;
	}
}

void SphereShape3::getMassProp(float density, float &mass, Vector3 &localInertia) const
{
	mass = volume * density;

	btVector3 inertia;
	((btSphereShape *)handle)->calculateLocalInertia(mass, inertia);

	localInertia = CAST_VECTOR3(inertia);
}