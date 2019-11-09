///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "CapsuleShape3.h"
#include "Physics3.h"
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
using namespace Magnum;

CapsuleShape3::CapsuleShape3()
: ConvexShape3(Shape3::CAPSULE)
{
}

CapsuleShape3::~CapsuleShape3()
{
	assert(handle==0);
}

bool CapsuleShape3::construct(CapsuleShape3::AxisDirection axisDir_, float radius_, float height_)
{
	assert(handle==0);

	btCapsuleShape *shape;
	switch(axisDir_)
	{
		case CapsuleShape3::X_AXIS:
			shape = new btCapsuleShapeX(radius_, height_);
		break;
		default:
		case CapsuleShape3::Y_AXIS:
			shape = new btCapsuleShape (radius_, height_);
		break;
		case CapsuleShape3::Z_AXIS:
			shape = new btCapsuleShapeZ(radius_, height_);
		break;
	};
	handle = shape;

	boundingBox.Min = Vector3(-radius_, -radius_, 0);
	boundingBox.Max = Vector3( radius_,  radius_, height_);

	volume  = Math::ONE_PI * radius_ * radius_ * height_ ;
	volume += 4.0/3.0 * Math::ONE_PI * radius_ * radius_ * radius_;

	return handle!=0;
}

void CapsuleShape3::destruct()
{
	if(handle)
	{
		delete ((btCapsuleShape *)handle);

		handle = 0;
	}
}

void CapsuleShape3::getMassProp(float density, float &mass, Vector3 &localInertia) const
{
	mass = volume * density;

	btVector3 inertia;
	((btCapsuleShape *)handle)->calculateLocalInertia(mass, inertia);

	localInertia = CAST_VECTOR3(inertia);
}