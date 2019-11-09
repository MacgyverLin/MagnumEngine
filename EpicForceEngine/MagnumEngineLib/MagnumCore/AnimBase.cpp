///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "AnimBase.h"
using namespace Magnum;

///////////////////////////////////////////////////////////
AnimBase::AnimBase()
: cb(0)
{
}

AnimBase::~AnimBase()
{
}

void AnimBase::invokeCallBack()
{
	if(cb)
	{
		cb->invoke(this);
	}
}

void AnimBase::setEventCallBack(Functor1<AnimBase *> *cb_)
{
	cb = cb_;
}

Functor1<AnimBase *> *AnimBase::getEventCallBack()
{
	return cb;
}