///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Selection3.h"
using namespace Magnum;

Selection3::Bound::Bound(Component::Owner &owner_)
: Component(owner_)
, category(0xffffffff)
, mask(0xffffffff)
, offsetTransform(Matrix4::IDENTITY)
, userData(0)
{
	Selection3::Manager::instance().bounds.push() = this;
}

Selection3::Bound::~Bound()
{
	int idx = Selection3::Manager::instance().bounds.search(this);
	if(idx>=0)
	{
		Selection3::Manager::instance().bounds.remove(idx);
	}
}

void Selection3::Bound::setOffsetTransform(const Matrix4 &offsetTransform_)
{
	offsetTransform = offsetTransform_;
}

const Matrix4 &Selection3::Bound::getOffsetTransform() const
{
	return offsetTransform;
}

void Selection3::Bound::setCategory(unsigned int category_)
{
	category = category_;
}

unsigned int Selection3::Bound::getCategory() const
{
	return category;
}

void Selection3::Bound::setMask(unsigned int mask_)
{
	mask = mask_;
}

unsigned int Selection3::Bound::getMask() const
{
	return mask;
}

void Selection3::Bound::setUserData(void *userData_)
{
	userData = userData_;
}

void *Selection3::Bound::getUserData() const
{
	return userData;
}

void Selection3::Bound::getInverseGlobalTransform(Matrix4 &globalTransform)
{
	globalTransform = (this->getOwner().getGlobalTransform() * offsetTransform).Inverse();
}

///////////////////////////////////////////////////////////////////////////////////
Selection3::Manager *Selection3::Manager::_instance = 0;

Selection3::Manager::Manager()
{
	assert(_instance==0);

	_instance = this;
}

Selection3::Manager::~Manager()
{
	assert(_instance!=0);

	_instance = 0;
}

bool Selection3::Manager::initiate()
{
	return true;
}

void Selection3::Manager::process()
{
}

void Selection3::Manager::pause()
{
}

void Selection3::Manager::resume()
{
}

void Selection3::Manager::terminate()
{
}

void Selection3::Manager::clear()
{
	bounds.clear();
}

Selection3::Manager &Selection3::Manager::instance()
{
	assert(_instance);

	return *_instance;
}

///////////////////////////////////////////////////////////////////////////////////
bool Selection3::Service::initiate()
{
	return Selection3::Manager::instance().initiate();
}

void Selection3::Service::process()
{
	Selection3::Manager::instance().process();
}

void Selection3::Service::pause()
{
	Selection3::Manager::instance().pause();
}

void Selection3::Service::resume()
{
	Selection3::Manager::instance().resume();
}

void Selection3::Service::terminate()
{
	Selection3::Manager::instance().terminate();
}

void Selection3::Service::clear()
{
	Selection3::Manager::instance().clear();
}