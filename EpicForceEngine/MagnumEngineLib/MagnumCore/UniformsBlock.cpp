///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "UniformsBlock.h"
using namespace Magnum;

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

int UniformsBlock::getUniformHandle(const char *name) const
{
	for(int i=0; i<uniforms.length(); i++)
	{
		if( strcasecmp(uniforms[i].getName(), name)==0 )
			return i;
	}

	return -1;
}

int UniformsBlock::getUniformHandleBySemantic(const char *sematic) const
{
	for(int i=0; i<uniforms.length(); i++)
	{
		if( strcasecmp(uniforms[i].getSemantic(), sematic)==0 )
			return i;
	}

	return -1;
}

GXUniform &UniformsBlock::getUniform(int handle)
{
	return uniforms[handle];
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