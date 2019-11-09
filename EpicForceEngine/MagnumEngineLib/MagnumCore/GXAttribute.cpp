#include "GXAttribute.h"

GXAttribute::GXAttribute()
{
}

GXAttribute::~GXAttribute()
{
}

void GXAttribute::construct(int location_, const GXShaderAttributeType &type_, const char *name_, int arraySize_, const char *semantic_)
{
	location		= location_;
	type			= type_;
	name			= name_;
	arraySize		= arraySize_;
	semantic		= semantic_;
}

int	GXAttribute::getLocation() const
{
	return location;
}

const GXShaderAttributeType &GXAttribute::getType() const
{
	return type;
}

const char *GXAttribute::getName() const
{
	return name.text();
}

int GXAttribute::getArraySize() const
{
	return arraySize;
}

const char *GXAttribute::getSemantic() const
{
	return semantic.text();
}