///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "EntityFieldWriter.h"
#include "ReflectedClassFieldWriter.h"
using namespace Magnum;

//////////////////////////////////////////////////////////////////////////////////////
EntityFieldWriter::EntityFieldWriter(const Entity &entity_)
: entity(entity_)
{
}

EntityFieldWriter::~EntityFieldWriter()
{
}

const Entity &EntityFieldWriter::getEntity()
{
	return entity;
}

bool EntityFieldWriter::write(OutputStream &os) const
{
	ReflectedClassFieldWriter<Entity> entityClassFieldWriter(&entity);

	if(!entityClassFieldWriter.write(os))
		return false;

	int numComponents = entity.getNumComponents();
	os << numComponents;
	for(int i=0; i<numComponents; i++)
	{
		const Component &component = *entity.getComponent(i);

		ReflectedClassFieldWriter<Component> componentClassFieldWriter(&component);

		if(!componentClassFieldWriter.write(os))
			return false;
	}

	return true;
}