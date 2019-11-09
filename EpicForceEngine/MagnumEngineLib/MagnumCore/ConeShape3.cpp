///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "ConeShape3.h"
#include "Physics3.h"
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
using namespace Magnum;

ConeShape3::ConeShape3()
: ConvexShape3(Shape3::CONE)
{
}

ConeShape3::~ConeShape3()
{
	assert(handle==0);
}

bool ConeShape3::construct(ConeShape3::AxisDirection axisDir_, float radius_, float height_)
{
	assert(handle==0);

	btConeShape *shape;
	switch(axisDir_)
	{
		case ConeShape3::X_AXIS:
			shape = new btConeShapeX(radius_, height_);
		break;
		default:
		case ConeShape3::Y_AXIS:
			shape = new btConeShape(radius_, height_);
		break;
		case ConeShape3::Z_AXIS:
			shape = new btConeShapeZ(radius_, height_);
		break;
	};
	handle = shape;

	btVector3 min, max;
	btTransform transform;
	transform.setIdentity();
	shape->getAabb(transform, min, max);

	boundingBox.Min = Vector3(min.x(), min.y(), min.z());
	boundingBox.Max = Vector3(max.x(), max.y(), max.z());
	Vector3 size(boundingBox.Max - boundingBox.Min);

	volume  = Math::ONE_PI * radius_ * radius_ * height_ / 3.0f;

	return handle!=0;
}

void ConeShape3::destruct()
{
	if(handle)
	{
		delete ((btConeShape *)handle);

		handle = 0;
	}
}

void ConeShape3::getMassProp(float density, float &mass, Vector3 &localInertia) const
{
	mass = volume * density;

	btVector3 inertia;
	((btConeShape *)handle)->calculateLocalInertia(mass, inertia);

	localInertia = CAST_VECTOR3(inertia);
}