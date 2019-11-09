///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Transform.h"
using namespace Magnum;

Transform::Transform()
: scale(Vector3::ONE)
, rotation(Quaternion::IDENTITY)
, translate(Vector3::ZERO)
{
}

Transform::Transform(const Vector3 &scale_, const Quaternion &rotation_, const Vector3 &translate_)
: scale(scale_)
, rotation(rotation_)
, translate(translate_)
{
}

Transform::~Transform()
{
}

void Transform::setTranslation(const Vector3 &translate_)
{
	translate = translate_;
}

const Vector3 &Transform::getTranslation() const
{
	return translate;
}

void Transform::setRotation(const Quaternion &rotation_)
{
	rotation = rotation_;
}

const Quaternion &Transform::getRotation() const
{
	return rotation;
}

void Transform::setScale(const Vector3 &scale_)
{
	scale = scale_;
}

const Vector3 &Transform::getScale() const
{
	return scale;
}

Transform Transform::operator * (const Transform &transform) const
{
	Transform rval;

	rval.translate = this->scale	* (this->rotation.Rotate(transform.translate)) + this->translate;
	rval.scale     = this->scale    * transform.scale;
	rval.rotation  = this->rotation * transform.rotation;	

	return rval;
}

Transform &Transform::operator *= (const Transform &transform)
{
	this->translate = this->scale	 * (this->rotation.Rotate(transform.translate)) + this->translate;
	this->scale     = this->scale    * transform.scale;
	this->rotation  = this->rotation * transform.rotation;
	
	return *this;
}

Vector3 Transform::operator *(const Vector3 &rkV) const
{
	return this->scale * this->rotation.Rotate(rkV) + this->translate;
}

Vector4 Transform::operator *(const Vector4 &rkV) const
{
	Vector3 vec3(this->scale * this->rotation.Rotate(Vector3(rkV[0], rkV[1], rkV[2])) + this->translate);

	return Vector4(vec3[0], vec3[1], vec3[2], 1.0);
}

Vector3 Transform::timesPositionVector(const Vector3 &rkV) const
{
	return this->scale * this->rotation.Rotate(rkV) + this->translate;
}

Vector3 Transform::timesDirectionVector(const Vector3 &rkV) const
{
	return this->scale * this->rotation.Rotate(rkV);
}

// other operations
Transform Transform::inverse() const
{
	Transform rval;

	rval.scale[0] = 1.0f / scale[0];
	rval.scale[1] = 1.0f / scale[1];
	rval.scale[2] = 1.0f / scale[2];

	rval.rotation[0] =  rotation[0];
	rval.rotation[1] = -rotation[1];
	rval.rotation[2] = -rotation[2];
	rval.rotation[3] = -rotation[3];

	rval.translate = -rval.scale * rotation.Rotate(translate);

	return rval;
}

void Transform::read(InputStream &is)
{
	is >> scale >> rotation >> translate;
}

void Transform::write(OutputStream &os) const
{
	os << scale << rotation << translate;
}