///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "ShaderProgramBlock.h"
using namespace Magnum;

ShaderProgramBlock::ShaderProgramBlock()
: handle(0)
{
}

ShaderProgramBlock::~ShaderProgramBlock()
{
}

ShaderProgramBlock &ShaderProgramBlock::operator = (const ShaderProgramBlock &other)
{
	this->vertexShaderCode	= other.vertexShaderCode;
	this->pixelShaderCode	= other.pixelShaderCode;

	this->handle			= other.handle;

	return *this;
}

void ShaderProgramBlock::read(InputStream &is)
{
	is >> vertexShaderCode;
	is >> pixelShaderCode;
}

void ShaderProgramBlock::write(OutputStream &os) const
{
	os << vertexShaderCode;
	os << pixelShaderCode;
}