#include "GXUniform.h"

GXUniform::GXUniform()
: invalid(false)
, location(-1)
, arraySize(0)
{
}

GXUniform::~GXUniform()
{
}

GXUniform &GXUniform::operator = (const GXUniform &other)
{ 
	invalid			= other.invalid;

	location		= other.location;
	type			= other.type;
	name			= other.name;
	arraySize		= other.arraySize;
	semantic		= other.semantic;

	buffer			= other.buffer;

	return *this;
}

void GXUniform::construct(int location_, const GXShaderUniformType &type_, const char *name_, int arraySize_, const char *semantic_)
{
	invalid			= true;

	location		= location_;
	type			= type_;
	name			= name_;
	arraySize		= arraySize_;
	semantic		= semantic_;

	int numBytes = type.getSize() * arraySize;
	buffer.resize(numBytes);
	System::Memset(&buffer[0], 0, numBytes);
}

void GXUniform::copyValue(const GXUniform &other)
{
	assert(buffer.length()==other.buffer.length());

	invalid			= true;

	buffer = other.buffer;
}

int	GXUniform::getLocation() const
{
	return location;
}

const GXShaderUniformType &GXUniform::getType() const
{
	return type;
}

const char *GXUniform::getName() const
{
	return name.text();
}

int GXUniform::getArraySize() const
{
	return arraySize;
}

const char *GXUniform::getSemantic() const
{
	return semantic.text();
}

void GXUniform::read(InputStream &is)
{
	is >> invalid;

	is >> location;
	is >> type;
	is >> name;
	is >> arraySize;
	is >> semantic;

	int numBytes;
	is >> numBytes;
	buffer.resize(numBytes);
	is.readX(&buffer[0], buffer.length());
}

void GXUniform::write(OutputStream &os) const
{
	os << invalid;

	os << location;
	os << type;
	os << name;
	os << arraySize;
	os << semantic;

	int numBytes = buffer.length();
	os << numBytes;
	os.writeX(&buffer[0], buffer.length());
}