///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited			 //
//																 //
// Author : Mac Lin									             //
// Module : EpicForceEngine										 //
// Date   : 19/Aug/2011											 //
//																 //
///////////////////////////////////////////////////////////////////
#include "ConvexHullShape3.h"
#include "Physics3.h"
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
using namespace Magnum;

ConvexHullShape3::ConvexHullShape3()
: Shape3(Shape3::CONVEXHULL)
{
}

ConvexHullShape3::~ConvexHullShape3()
{
	assert(handle==0);
}

bool ConvexHullShape3::construct(Vector3 *vertex_, int numVertices_)
{
	assert(handle==0);

	btConvexHullShape *shape = new btConvexHullShape( ((float *)vertex_), numVertices_, sizeof(Vector3) );
	handle = shape;

	btVector3 min, max;
	btTransform transform;
	transform.setIdentity();
	shape->getAabb(transform, min, max);

	boundingBox.Min = Vector3(min.x(), min.y(), min.z());
	boundingBox.Max = Vector3(max.x(), max.y(), max.z());
	Vector3 size(boundingBox.Max - boundingBox.Min);
	volume = size.X()*size.Y()*size.Z();

	return handle!=0;
}

void ConvexHullShape3::destruct()
{
	if(handle)
	{
		delete ((btConvexHullShape *)handle);

		handle = 0;
	}
}