///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited			 //
//																 //
// Author : Mac Lin									             //
// Module : EpicForceEngine										 //
// Date   : 19/Aug/2011											 //
//																 //
///////////////////////////////////////////////////////////////////
#ifndef _ConvexHullShape3_h_
#define _ConvexHullShape3_h_

#include "Stage.h"
#include "Vector3.h"
#include "AABB3.h"
#include "Shape3.h"
using namespace Magnum;

namespace Magnum
{

class ConvexHullShape3 : public Shape3
{
public:
	ConvexHullShape3();
	~ConvexHullShape3();

	bool construct(Vector3 *vertex_, int numVertices_);
	void destruct();

	//virtual int32 GetChildCount() const = 0;
	//virtual bool TestPoint(const b2Transform& xf, const b2Vec2& p) const = 0;
	//virtual bool RayCast(b2RayCastOutput* output, const b2RayCastInput& input, const b2Transform& transform, int32 childIndex) const = 0;
	//virtual void ComputeAABB(b2AABB* aabb, const b2Transform& xf, int32 childIndex) const = 0;
	//virtual void ComputeMass(b2MassData* massData, float32 density) const = 0;
protected:
private:
};

};

#endif