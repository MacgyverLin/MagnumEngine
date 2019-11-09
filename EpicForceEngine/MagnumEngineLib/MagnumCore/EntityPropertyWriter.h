///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _EntityPropertyWriter_h_
#define _EntityPropertyWriter_h_

#include "Stage.h"
#include "Entity.h"
#include "InputStream.h"
#include "OutputStream.h"
using namespace Magnum;

namespace Magnum
{

class EntityPropertyWriter
{
public:
	EntityPropertyWriter(const Entity &entity_);
	~EntityPropertyWriter();

	const Entity &getEntity();

	bool write(OutputStream &os) const;
private:
	const Entity &entity;
};

}

#endif
