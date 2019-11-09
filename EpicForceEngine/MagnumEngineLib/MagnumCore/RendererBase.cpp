///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "RendererBase.h"

RendererBase::RendererBase(Component::Owner &owner_)
: Component(owner_)
{
	Video::Manager::instance().renderers.push() = this;
}

RendererBase::~RendererBase()
{
	int idx = Video::Manager::instance().renderers.search(this);
	if(idx>=0)
	{
		Video::Manager::instance().renderers.remove(idx);
	}
}

int RendererBase::compare(const void *left, const void *right)
{
	return (*((const RendererBase **)left))->getOrder() - (*((const RendererBase **)right))->getOrder();
}