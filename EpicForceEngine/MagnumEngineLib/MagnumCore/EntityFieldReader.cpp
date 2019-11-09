///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "EntityFieldReader.h"
#include "ReflectedClassFieldReader.h"
using namespace Magnum;

//////////////////////////////////////////////////////////////////////////////////////
EntityFieldReader::EntityFieldReader(Entity &entity_)
: entity(entity_)
{
}

EntityFieldReader::~EntityFieldReader()
{
}

Entity &EntityFieldReader::getEntity()
{
	return entity;
}

bool EntityFieldReader::read(InputStream &is)
{
	ReflectedClassFieldReader<Entity> entityFieldReader(&entity);

	if(!entityFieldReader.read(is))
		return false;

	int numComponents;
	is >> numComponents;
	assert(numComponents==entity.getNumComponents());
	for(int i=0; i<numComponents; i++)
	{
		Component &component = *entity.getComponent(i);

		ReflectedClassFieldReader<Component> componentFieldReader(&component);

		if(!componentFieldReader.read(is))
			return false;
	}

	return true;
}