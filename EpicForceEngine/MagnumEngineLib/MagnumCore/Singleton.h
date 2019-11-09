///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Singleton_h_
#define _Singleton_h_

#include "Stage.h"

namespace Magnum
{

template <typename T> class Singleton
{
protected:
	static T *_instance;

public:		
	static T &instance()
	{
		assert(_instance!=0);
		return *_instance;
	}

	static bool instantiated()
	{
		return _instance!=0;
	}

	Singleton()
	{
		assert(!_instance);
		_instance=(T*)this;
	}

	virtual ~Singleton()
	{
		assert(_instance!=0);
		_instance=0;
	}
};

template <typename T> T* Singleton<T>::_instance=0;
}


#endif
