///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _EntityFieldWriter_h_
#define _EntityFieldWriter_h_

#include "Stage.h"
#include "Entity.h"
#include "InputStream.h"
#include "OutputStream.h"
using namespace Magnum;

namespace Magnum
{

class EntityFieldWriter
{
public:
	EntityFieldWriter(const Entity &entity_);
	~EntityFieldWriter();

	const Entity &getEntity();

	bool write(OutputStream &os) const;
private:
	const Entity &entity;
};

}

#endif
