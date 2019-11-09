///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "EntityPropertyReader.h"
#include "ReflectedClassPropertyReader.h"
using namespace Magnum;

//////////////////////////////////////////////////////////////////////////////////////
EntityPropertyReader::EntityPropertyReader(Entity &entity_)
: entity(entity_)
{
}

EntityPropertyReader::~EntityPropertyReader()
{
}

Entity &EntityPropertyReader::getEntity()
{
	return entity;
}

bool EntityPropertyReader::read(InputStream &is)
{
	ReflectedClassPropertyReader<Entity> entityPropertyReader(&entity);

	if(!entityPropertyReader.read(is))
		return false;

	int numComponents;
	is >> numComponents;
	assert(numComponents==entity.getNumComponents());
	for(int i=0; i<numComponents; i++)
	{
		Component &component = *entity.getComponent(i);

		ReflectedClassPropertyReader<Component> componentPropertyReader(&component);

		if(!componentPropertyReader.read(is))
			return false;
	}

	return true;
}