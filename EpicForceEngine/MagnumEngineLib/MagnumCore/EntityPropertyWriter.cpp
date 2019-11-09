///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "EntityPropertyWriter.h"
#include "ReflectedClassPropertyWriter.h"
using namespace Magnum;

//////////////////////////////////////////////////////////////////////////////////////
EntityPropertyWriter::EntityPropertyWriter(const Entity &entity_)
: entity(entity_)
{
}

EntityPropertyWriter::~EntityPropertyWriter()
{
}

const Entity &EntityPropertyWriter::getEntity()
{
	return entity;
}

bool EntityPropertyWriter::write(OutputStream &os) const
{
	ReflectedClassPropertyWriter<Entity> entityPropertyWriter(&entity);

	if(!entityPropertyWriter.write(os))
		return false;

	int numComponents = entity.getNumComponents();
	os << numComponents;
	for(int i=0; i<numComponents; i++)
	{
		const Component &component = *entity.getComponent(i);

		ReflectedClassPropertyWriter<Component> componentPropertyWriter(&component);

		if(!componentPropertyWriter.write(os))
			return false;
	}

	return true;
}