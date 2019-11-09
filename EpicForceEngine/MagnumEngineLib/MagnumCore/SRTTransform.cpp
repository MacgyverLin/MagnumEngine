///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "SRTTransform.h"
using namespace Magnum;

SRTTransform::SRTTransform()
{
}

SRTTransform::SRTTransform(const Vector3 &s_, const Vector3 &r_, const Vector3 &t_)
: s(s_)
, r(r_)
, t(t_)
, changed(0)
{
}

SRTTransform::SRTTransform(const SRTTransform &srtTransform_)
{
	*this = srtTransform_;
}

SRTTransform &SRTTransform::operator = (const SRTTransform &srtTransform_)
{
	this->s	= srtTransform_.s;
	this->r	= srtTransform_.r;
	this->t	= srtTransform_.t;

	this->changed	= srtTransform_.changed;

	return *this;
}

SRTTransform::~SRTTransform()
{
}

Matrix4 SRTTransform::toMatrix4() const
{
	Matrix4 mat;
	mat.FromSRT(s, r, t);

	return mat;
}

Vector3 &SRTTransform::S()
{
	return s;
}

const Vector3 &SRTTransform::S() const
{
	return s;
}

Vector3 &SRTTransform::R()
{
	return r;
}

const Vector3 &SRTTransform::R() const
{
	return r;
}

Vector3 &SRTTransform::T()
{
	return t;
}

const Vector3 &SRTTransform::T() const
{
	return t;
}

bool SRTTransform::operator == (const SRTTransform &srtTransform_) const
{
	return	s == srtTransform_.s &&
			r == srtTransform_.r &&
			t == srtTransform_.t;
}

bool SRTTransform::operator <  (const SRTTransform &srtTransform_) const
{
	if( s < srtTransform_.s)
	{
		return true;
	}
	else if( s == srtTransform_.s)
	{
		if( r < srtTransform_.r)
		{
			return true;
		}
		else if( r==srtTransform_.r)
		{
			return (t < srtTransform_.t);
		}
	}

	return false;
}

void SRTTransform::read(InputStream &is)
{
	is >> changed >> s >> r >> t;
}

void SRTTransform::write(OutputStream &os) const
{
	os << changed << s << r << t;
}