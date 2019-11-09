///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _SRTTransform_h_
#define _SRTTransform_h_

#include "Stage.h"
#include "EMath.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Vector3.h"
#include "Matrix4.h"

namespace Magnum
{

class SRTTransform
{
public:
	SRTTransform();
	SRTTransform(const Vector3 &s_, const Vector3 &r_, const Vector3 &t_);
	SRTTransform(const SRTTransform &srtTransform_);
	SRTTransform &operator = (const SRTTransform &srtTransform_);
	~SRTTransform();

	Matrix4 toMatrix4() const;

	Vector3 &S();
	const Vector3 &S() const;
	
	Vector3 &R();
	const Vector3 &R() const;

	Vector3 &T();
	const Vector3 &T() const;

	bool operator == (const SRTTransform &srtTransform) const;
	bool operator <  (const SRTTransform &srtTransform) const;

	void read(InputStream &is);
	void write(OutputStream &os) const;

	int changed;
private:
	Vector3 s;
	Vector3 r;
	Vector3 t;
};

};

#endif