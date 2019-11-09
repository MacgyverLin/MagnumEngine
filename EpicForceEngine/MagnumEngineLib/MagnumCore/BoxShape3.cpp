///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "BoxShape3.h"
#include "Physics3.h"
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
using namespace Magnum;

BoxShape3::BoxShape3()
: ConvexShape3(Shape3::BOX)
{
}

BoxShape3::~BoxShape3()
{
	assert(handle==0);
}

bool BoxShape3::construct(const Vector3 &halfExtent_)
{
	assert(handle==0);

	btBoxShape *shape	= new btBoxShape( btVector3(halfExtent_.X(), halfExtent_.Y(), halfExtent_.Z()) );
	handle				= shape;

	boundingBox.Min = Vector3(-halfExtent_.X(), -halfExtent_.Y(), -halfExtent_.Z());
	boundingBox.Max = Vector3( halfExtent_.X(),  halfExtent_.Y(),  halfExtent_.Z());
	Vector3 size(boundingBox.Max - boundingBox.Min);
	volume = size.X()*size.Y()*size.Z();
	
	return handle!=0;
}

void BoxShape3::destruct()
{
	if(handle)
	{
		delete ((btBoxShape *)handle);

		handle = 0;
	}
}

void BoxShape3::getMassProp(float density, float &mass, Vector3 &localInertia) const
{
	mass = volume * density;

	btVector3 inertia;
	((btBoxShape *)handle)->calculateLocalInertia(mass, inertia);

	localInertia = CAST_VECTOR3(inertia);
}