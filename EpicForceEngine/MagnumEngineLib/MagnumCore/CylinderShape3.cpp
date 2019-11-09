///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "CylinderShape3.h"
#include "Physics3.h"
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
using namespace Magnum;

CylinderShape3::CylinderShape3()
: ConvexShape3(Shape3::CYLINDER)
{
}

CylinderShape3::~CylinderShape3()
{
	assert(handle==0);
}

bool CylinderShape3::construct(CylinderShape3::AxisDirection axisDir_, float radius_, float height_)
{
	assert(handle==0);

	btCylinderShape *shape;
	switch(axisDir_)
	{
		case CylinderShape3::X_AXIS:
			shape = new btCylinderShapeX(btVector3(height_, radius_, radius_));
		break;
		default:
		case CylinderShape3::Y_AXIS:
			shape = new btCylinderShape(btVector3(radius_, height_, radius_));
		break;
		case CylinderShape3::Z_AXIS:
			shape = new btCylinderShapeZ(btVector3(radius_, radius_, height_));
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

	volume  = Math::ONE_PI * radius_ * radius_ * height_;

	return handle!=0;
}

void CylinderShape3::destruct()
{
	if(handle)
	{
		delete ((btCylinderShape *)handle);
		handle = 0;
	}
}

void CylinderShape3::getMassProp(float density, float &mass, Vector3 &localInertia) const
{
	mass = volume * density;

	btVector3 inertia;
	((btCylinderShape *)handle)->calculateLocalInertia(mass, inertia);

	localInertia = CAST_VECTOR3(inertia);
}