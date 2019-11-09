///////////////////////////////////////////////////////////////////
// Copyright(c) 2011-, EpicForce Entertainment Limited
// 
// Author : Mac Lin
// Module : EpicForceEngine
// Date   : 19/Aug/2011
// 
///////////////////////////////////////////////////////////////////
#include "UniformsBlock.h"
using namespace EpicForce;

UniformsBlock::UniformsBlock()
{
}

UniformsBlock::~UniformsBlock()
{
}

UniformsBlock &UniformsBlock::operator = (const UniformsBlock &other) 
{
	this->uniforms = other.uniforms;

	return *this;
}

int UniformsBlock::getNumUniforms() const
{
	return uniforms.length();
}

int UniformsBlock::getUniformIdx(const char *name) const
{
	for(int i=0; i<uniforms.length(); i++)
	{
		if( strcasecmp(uniforms[i].getName(), name)==0 )
			return i;
	}

	return -1;
}

int UniformsBlock::getUniformIdxBySemantic(const char *sematic) const
{
	for(int i=0; i<uniforms.length(); i++)
	{
		if( strcasecmp(uniforms[i].getSemantic(), sematic)==0 )
			return i;
	}

	return -1;
}

GXUniform &UniformsBlock::getUniform(const char *name)
{
	int idx = getUniformIdx(name);
	assert(idx>=0);

	return uniforms[idx];
}

GXUniform &UniformsBlock::getUniformBySemantic(const char *name)
{
	int idx = getUniformIdxBySemantic(name);
	assert(idx>=0);

	return uniforms[idx];
}

GXUniform &UniformsBlock::getUniform(int i)
{
	return uniforms[i];
}

void UniformsBlock::read(InputStream &is)
{
	VectorRead<GXUniform> uniformsVectorRead(uniforms);
	is >> uniformsVectorRead;
}

void UniformsBlock::write(OutputStream &os) const
{
	VectorWrite<GXUniform> uniformsVectorWrite(uniforms);
	os << uniformsVectorWrite;
}