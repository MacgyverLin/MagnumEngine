///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#include "VertexDesc.h"
using namespace EpicForce;

///////////////////////////////////////////////////////////////////
VertexDesc::VertexDesc()
{
}

VertexDesc::~VertexDesc()
{
}

bool VertexDesc::construct(const Vector<GXVertexFormat> &vertexFormats_, 
						   const Vector<GXVertexStreamSource> &vertexStreamSources_)
{
	vertexFormats		= vertexFormats_;
	vertexStreamSources = vertexStreamSources_;

	return true;
}

int VertexDesc::numAttributes() const
{
	return vertexFormats.length();
}

const GXVertexFormat &VertexDesc::getVertexFormat(int i) const
{
	return vertexFormats[i];
}

const GXVertexStreamSource &VertexDesc::getVertexStreamSource(int i) const
{
	return vertexStreamSources[i];
}

bool VertexDesc::operator == (const VertexDesc &other) const
{
	if(other.vertexFormats.length()!=vertexFormats.length())
		return false;
	if(other.vertexStreamSources.length()!=vertexStreamSources.length())
		return false;

	for(int i=0; i<vertexFormats.length(); i++)
	{
		if( !(other.vertexFormats[i]==vertexFormats[i]) )
			return false;
	}

	for(int i=0; i<vertexStreamSources.length(); i++)
	{
		if( !(other.vertexStreamSources[i]==vertexStreamSources[i]) )
			return false;
	}

	return true;
}

void VertexDesc::read(InputStream &is)
{
	int numFormats;
	is >> numFormats;
	vertexFormats.resize(numFormats);
	for(int i=0; i<vertexFormats.length(); i++)
		is >> vertexFormats[i];

	int numVertexStreamSources;
	is >> numVertexStreamSources;
	vertexStreamSources.resize(numVertexStreamSources);
	for(int i=0; i<vertexStreamSources.length(); i++)
		is >> vertexStreamSources[i];
}

void VertexDesc::write(OutputStream &os) const
{
	int numFormats = vertexFormats.length();
	os << numFormats;
	for(int i=0; i<vertexFormats.length(); i++)
		os << vertexFormats[i];

	int numVertexStreamSources = vertexStreamSources.length();
	os << numVertexStreamSources;
	for(int i=0; i<vertexStreamSources.length(); i++)
		os << vertexStreamSources[i];
}