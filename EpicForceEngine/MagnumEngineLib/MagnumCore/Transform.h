///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Transform_h_
#define _Transform_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix4.h"

namespace Magnum
{

class Transform
{
public:
	Transform();
	Transform(const Vector3 &scale, const Quaternion &rotation, const Vector3 &translate);
	~Transform();

	void setTranslation(const Vector3 &translate);
	const Vector3 &getTranslation() const;

	void setRotation(const Quaternion &rotation);
	const Quaternion &getRotation() const;

	void setScale(const Vector3 &scale);
	const Vector3 &getScale() const;

    Transform operator *(const Transform &transform) const;
	Transform &operator *=(const Transform &transform);
	Vector3 operator *(const Vector3 &v) const;
	Vector4 operator *(const Vector4 &v) const;
	Vector3 timesPositionVector(const Vector3 &v) const;
	Vector3 timesDirectionVector(const Vector3 &v) const;

    // other operations
    Transform inverse() const;

	void read(InputStream &is);
	void write(OutputStream &os) const;
private:
	Vector3		scale;
	Quaternion	rotation;
	Vector3		translate;
};

};

#endif