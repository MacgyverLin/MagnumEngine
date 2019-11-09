///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Delegate.h"
using namespace Magnum;

void Dispatch::insert(Functor &functor)
{
	assert(!_post.has(functor));
	_post.insert(functor);
}

void Dispatch::remove(Functor &functor)
{
	_post.remove(functor);
}

void Dispatch::capture(Functor &functor)
{
	_capture=&functor;
}

void Dispatch::release()
{
	_capture=0;
}

void Dispatch::stop()
{
	_post.stop();
}

void Dispatch::clear()
{
	release();
	_post.clear();
}

bool Dispatch::dispatch(const char *name)
{
	if(_capture)
	{
		_capture->invoke();
		return true;
	}
	
	if(!name)
		return _post.forward(&Functor::invoke);
	else
	{
		if(!_post.begin_forward())
			return false;
		bool did=false;
		do
		{	Functor &f=_post.current();
			if( strcasecmp(name,f.name)==0 )
			{
				did=true;
				f.invoke();
			}
		} while(_post.next());
		return did;
	}
	return true;
}

Dispatch::Dispatch()
: _capture(0)
{
}

Dispatch::~Dispatch()
{
}