///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "SkeletalAnimBase.h"
using namespace Magnum;

SkeletalAnimBase::SkeletalAnimBase() 
: AnimBase()
{
}

SkeletalAnimBase::~SkeletalAnimBase()
{
}

void SkeletalAnimBase::getLocalTransform(int boneIdx_, Matrix4 &mat_) const
{
	Vector10 v;
	getVector10(boneIdx_, v);
	v.ToMatrix4(mat_);
}

void SkeletalAnimBase::getSystemTransform(int boneIdx_, Matrix4 &mat_) const
{
	int parentIdx = getBoneParentIndex(boneIdx_);
	if( parentIdx!=-1 ) 
	{
		Matrix4 localMatrix, parentSystemMatrix;
		getSystemTransform(parentIdx, parentSystemMatrix);
		getLocalTransform(boneIdx_, localMatrix);

		mat_ = parentSystemMatrix * localMatrix;
	}
	else
	{
		getLocalTransform(boneIdx_, mat_);
	}
}