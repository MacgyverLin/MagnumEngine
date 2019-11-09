///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _EntityPropertyReader_h_
#define _EntityPropertyReader_h_

#include "Stage.h"
#include "Entity.h"
#include "InputStream.h"
#include "OutputStream.h"
using namespace Magnum;

namespace Magnum
{

class EntityPropertyReader
{
public:
	EntityPropertyReader(Entity &entity_);
	~EntityPropertyReader();

	Entity &getEntity();

	bool read(InputStream &is);
private:
	Entity &entity;
};

}

#endif
