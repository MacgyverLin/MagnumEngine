///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "AttributesBlock.h"
using namespace Magnum;

AttributesBlock::AttributesBlock()
{
}

AttributesBlock::~AttributesBlock()
{
}

AttributesBlock &AttributesBlock::operator = (const AttributesBlock &other)
{
	attributeTypes		= other.attributeTypes;
	vertexFormats		= other.vertexFormats;	
	attributeNames		= other.attributeNames;	
	vertexStreamSources	= other.vertexStreamSources;

	return *this;
}

bool AttributesBlock::operator == (const AttributesBlock &other) const
{
	if(other.attributeTypes.length()!=attributeTypes.length())
		return false;
	if(other.vertexFormats.length()!=vertexFormats.length())
		return false;
	if(other.attributeNames.length()!=attributeNames.length())
		return false;
	if(other.vertexStreamSources.length()!=vertexStreamSources.length())
		return false;

	for(int i=0; i<attributeTypes.length(); i++)
	{
		if( !(other.attributeTypes[i]==attributeTypes[i]) )
			return false;
	}

	for(int i=0; i<vertexFormats.length(); i++)
	{
		if( !(other.vertexFormats[i]==vertexFormats[i]) )
			return false;
	}

	for(int i=0; i<attributeNames.length(); i++)
	{
		if( !(other.attributeNames[i]==attributeNames[i]) )
			return false;
	}

	for(int i=0; i<vertexStreamSources.length(); i++)
	{
		if( !(other.vertexStreamSources[i]==vertexStreamSources[i]) )
			return false;
	}

	return true;
}

int AttributesBlock::getNumAttributes() const
{
	return attributeTypes.length();
}

const GXShaderAttributeType &AttributesBlock::getAttributeType(int i) const
{
	return attributeTypes[i];
}

const GXVertexFormat &AttributesBlock::getVertexFormat(int i) const
{
	return vertexFormats[i];
}

const char *AttributesBlock::getAttributeName(int i) const
{
	return attributeNames[i];
}

const GXVertexStreamSource &AttributesBlock::getVertexStreamSource(int i) const
{
	return vertexStreamSources[i];
}

void AttributesBlock::read(InputStream &is)
{
	int numEntries;
	is >> numEntries;

	attributeTypes.resize(numEntries);
	vertexFormats.resize(numEntries);
	attributeNames.resize(numEntries);
	vertexStreamSources.resize(numEntries);

	for(int i=0; i<attributeTypes.length(); i++)
		is >> attributeTypes[i];

	for(int i=0; i<vertexFormats.length(); i++)
		is >> vertexFormats[i];

	for(int i=0; i<attributeNames.length(); i++)
		is >> attributeNames[i];

	for(int i=0; i<vertexStreamSources.length(); i++)
		is >> vertexStreamSources[i];
}

void AttributesBlock::write(OutputStream &os) const
{
	int numEntries	= attributeTypes.length();
	os << numEntries;

	for(int i=0; i<attributeTypes.length(); i++)
		os << attributeTypes[i];

	for(int i=0; i<vertexFormats.length(); i++)
		os << vertexFormats[i];

	for(int i=0; i<attributeNames.length(); i++)
		os << attributeNames[i];

	for(int i=0; i<vertexStreamSources.length(); i++)
		os << vertexStreamSources[i];
}