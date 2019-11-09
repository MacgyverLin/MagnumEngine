#include "GXShaderProgram.h"
#include "GXContext.h"
#include "gldef.h"

GXShaderProgram::GXShaderProgram(const char *vpFileName_, const char *fpFileName_,
								 const Vector<String> &attributeNames_)
: invalid(true)
, handle(0)
, vertexShaderHandle(0)
, pixelShaderHandle(0)
{
	if(!FileIO::exists(vpFileName_))
		return;
	if(!FileIO::exists(fpFileName_))
		return;

	int vpLength = FileIO::length(vpFileName_);
	int fpLength = FileIO::length(fpFileName_);
	Vector<char> vpFileImage;
	Vector<char> fpFileImage;
	vpFileImage.resize(vpLength+1);
	fpFileImage.resize(fpLength+1);

	bool loadVPOK = FileIO::load(vpFileName_, &vpFileImage[0], vpLength, 0);
	vpFileImage[vpLength] = 0;
	bool loadFPOK = FileIO::load(fpFileName_, &fpFileImage[0], fpLength, 0);
	fpFileImage[fpLength] = 0;

	if(loadVPOK && loadFPOK)
	{
		createShaderProgram(&vpFileImage[0], &fpFileImage[0], attributeNames_);
	}
}

GXShaderProgram::GXShaderProgram(const char *vpFileImage_, unsigned int vpFileImagelength_, 
								 const char *fpFileImage_, unsigned int fpFileImagelength_,
								 const Vector<String> &attributeNames_)
: invalid(true)
, handle(0)
, vertexShaderHandle(0)
, pixelShaderHandle(0)
{
	createShaderProgram(vpFileImage_, fpFileImage_, attributeNames_);
}

GXShaderProgram::~GXShaderProgram()
{
	const GXShaderProgram *shaderProgram = GXContext::instance().getShaderProgram();
	if(shaderProgram==this)
	{
		GXContext::instance().setShaderProgram(0);
	}

	deleteShaderProgram();
}

int GXShaderProgram::getAttributeCount() const
{
	return attributes.length();
}

int GXShaderProgram::getAttributeIdx(const char *name_) const
{
	for(int i=0; i<attributes.length(); i++)
	{
		if(attributes[i].name==name_)
		{
			return i;
		}
	}

	return -1;
}

int GXShaderProgram::getAttributeLocation(int i_) const
{
	assert(i_ < attributes.length() );

	return attributes[i_].location;
}

const GXShaderAttributeType &GXShaderProgram::getAttributeType(int i_) const
{
	assert(i_ < attributes.length() );

	return attributes[i_].type;
}

const char *GXShaderProgram::getAttributeName(int i_) const
{
	assert(i_ < attributes.length() );

	return attributes[i_].name.text();
}

const char *GXShaderProgram::getAttributeSemantic(int i_) const
{
	assert(i_ < attributes.length() );

	return attributes[i_].semantic.text();
}

int GXShaderProgram::getAttributeArraySize(int i_) const
{
	assert(i_ < attributes.length() );

	return attributes[i_].arraySize;
}

int GXShaderProgram::getUniformCount() const
{
	return uniforms.length();
}

int GXShaderProgram::getUniformIdx(const char *name_) const
{
	for(int i=0; i<uniforms.length(); i++)
	{
		if(uniforms[i].name==name_)
		{
			return i;
		}
	}

	return -1;
}

/*
const char *GXShaderProgram::getUniformBinding(int index) const
{
	for(int i=0; i<uniformLocations.length(); i++)
	{
		if(uniformLocations[i]==index)
		{
			return uniformNames[i].c_str();
		}
	}

	return "";
}

void GXShaderProgram::setUniformBinding(int index, const char *name)
{
	assert(index < uniformNames.length() );

	uniformNames[index] = name;
}

const char *GXShaderProgram::getAttributeBinding(int index) const
{
	for(int i=0; i<attributeLocations.length(); i++)
	{
		if(attributeLocations[i]==index)
		{
			return attributeNames[i].c_str();
		}
	}

	return "";
}


void GXShaderProgram::setAttributeBinding(int index, const char *name)
{
	assert(index < attributeNames.length() );

	attributeNames[index] = name;
}
*/

int GXShaderProgram::getUniformLocation(int i_) const
{
	assert(i_ < uniforms.length() );

	return uniforms[i_].location;
}

const GXShaderUniformType &GXShaderProgram::getUniformType(int i_) const
{
	assert(i_ < uniforms.length() );

	return uniforms[i_].type;
}

const char *GXShaderProgram::getUniformName(int i_) const
{
	assert(i_ < uniforms.length() );

	return uniforms[i_].name.text();
}

const char *GXShaderProgram::getUniformSemantic(int i_) const
{
	assert(i_ < uniforms.length() );

	return uniforms[i_].semantic.text();
}

int GXShaderProgram::getUniformArraySize(int i_) const
{
	assert(i_ < uniforms.length() );

	return uniforms[i_].arraySize;
}

void GXShaderProgram::uniformBool(const GXUniform &uniform)
{
	glUniform1iv(uniform.location, uniform.arraySize, (int *)(&uniform.buffer[0]));

	checkGLError("uniformBool");
}

void GXShaderProgram::uniformBVec2(const GXUniform &uniform)
{
	glUniform2iv(uniform.location, uniform.arraySize, (int *)(&uniform.buffer[0]));

	checkGLError("uniformBool2");
}

void GXShaderProgram::uniformBVec3(const GXUniform &uniform)
{
	glUniform3iv(uniform.location, uniform.arraySize, (int *)(&uniform.buffer[0]));

	checkGLError("uniformBool3");
}

void GXShaderProgram::uniformBVec4(const GXUniform &uniform)
{
	glUniform4iv(uniform.location, uniform.arraySize, (int *)(&uniform.buffer[0]));

	checkGLError("uniformBool4");
}

void GXShaderProgram::uniformInt(const GXUniform &uniform)
{
	glUniform1iv(uniform.location, uniform.arraySize, (int *)(&uniform.buffer[0]));

	checkGLError("uniformInt");
}

void GXShaderProgram::uniformIVec2(const GXUniform &uniform)
{
	glUniform2iv(uniform.location, uniform.arraySize, (int *)(&uniform.buffer[0]));

	checkGLError("uniformInt2");
}

void GXShaderProgram::uniformIVec3(const GXUniform &uniform)
{
	glUniform3iv(uniform.location, uniform.arraySize, (int *)(&uniform.buffer[0]));

	checkGLError("uniformInt3");
}

void GXShaderProgram::uniformIVec4(const GXUniform &uniform)
{
	glUniform4iv(uniform.location, uniform.arraySize, (int *)(&uniform.buffer[0]));

	checkGLError("uniformInt4");
}

void GXShaderProgram::uniformFloat(const GXUniform &uniform)
{
	glUniform1fv(uniform.location, uniform.arraySize, (float *)(&uniform.buffer[0]));

	checkGLError("uniformFloat");
}

void GXShaderProgram::uniformVec2(const GXUniform &uniform)
{
	glUniform2fv(uniform.location, uniform.arraySize, (float *)(&uniform.buffer[0]));

	checkGLError("uniformFloat2");
}

void GXShaderProgram::uniformVec3(const GXUniform &uniform)
{
	glUniform3fv(uniform.location, uniform.arraySize, (float *)(&uniform.buffer[0]));

	checkGLError("uniformFloat3");
}

void GXShaderProgram::uniformVec4(const GXUniform &uniform)
{
	glUniform4fv(uniform.location, uniform.arraySize, (float *)(&uniform.buffer[0]));

	checkGLError("uniformFloat4");
}

void GXShaderProgram::uniformMat2(const GXUniform &uniform)
{
	glUniformMatrix2fv(uniform.location, uniform.arraySize, false, (float *)(&uniform.buffer[0]));

	checkGLError("uniformFloat2x2");
}

void GXShaderProgram::uniformMat3(const GXUniform &uniform)
{
	glUniformMatrix3fv(uniform.location, uniform.arraySize, false, (float *)(&uniform.buffer[0]));

	checkGLError("uniformFloat3x3");
}

void GXShaderProgram::uniformMat4(const GXUniform &uniform)
{
	glUniformMatrix4fv(uniform.location, uniform.arraySize, false, (float *)(&uniform.buffer[0]));

	checkGLError("uniformFloat4x4");
}

void GXShaderProgram::uniformSampler2D(const GXUniform &uniform)
{
	glUniform1iv(uniform.location, uniform.arraySize, (int *)(&uniform.buffer[0]));

	checkGLError("uniformSampler2D");
}

void GXShaderProgram::uniformSamplerCube(const GXUniform &uniform)
{
	glUniform1iv(uniform.location, uniform.arraySize, (int *)(&uniform.buffer[0]));

	checkGLError("uniformSamplerCube");
}

typedef void (*UniformNativeFunc)(const GXUniform &uniform);

UniformNativeFunc uniformNativeFuncs[] =
{
	GXShaderProgram::uniformBool,
	GXShaderProgram::uniformBVec2,
	GXShaderProgram::uniformBVec3,
	GXShaderProgram::uniformBVec4,
	GXShaderProgram::uniformInt,
	GXShaderProgram::uniformIVec2,
	GXShaderProgram::uniformIVec3,
	GXShaderProgram::uniformIVec4,
	GXShaderProgram::uniformFloat,
	GXShaderProgram::uniformVec2,
	GXShaderProgram::uniformVec3,
	GXShaderProgram::uniformVec4,
	GXShaderProgram::uniformMat2,
	GXShaderProgram::uniformMat3,
	GXShaderProgram::uniformMat4,
	GXShaderProgram::uniformSampler2D,
	GXShaderProgram::uniformSamplerCube,
};

void GXShaderProgram::update()
{
	checkGLError("update");
	if(invalid)
	{
		for(int i=0; i<uniforms.length(); i++)
		{
			if(uniforms[i].invalid)
			{
				int order = uniforms[i].type;
				assert( order < sizeof(uniformNativeFuncs) / sizeof(uniformNativeFuncs[0]) );

				uniformNativeFuncs[order](uniforms[i]);

				uniforms[i].invalid = false;
			}
		}

		invalid = false;
	}
}

bool GXShaderProgram::createShaderProgram(const char *pVertexSource_, const char *pFragmentSource_,
										  const Vector<String> &attributeNames_)
{
	handle = glCreateProgram();

	if(handle)
	{
		String psCodeHeader = String("#ifdef GL_ES\n #ifdef GL_FRAGMENT_PRECISION_HIGH\n precision highp float;\n	#else\n	precision mediump float;\n #endif\n	#endif\n\n") + pFragmentSource_;
		String vsCodeHeader = String("#ifdef GL_ES\n precision mediump float;\n #endif\n\n") + pVertexSource_;

		pixelShaderHandle  = createShader(GL_FRAGMENT_SHADER, psCodeHeader.text());
		vertexShaderHandle = createShader(GL_VERTEX_SHADER, vsCodeHeader.text());

		glAttachShader(handle, vertexShaderHandle);
		checkGLError("glAttachShader");
	
		glAttachShader(handle, pixelShaderHandle );
		checkGLError("glAttachShader");

		for(int i=0; i<attributeNames_.length(); i++)
		{
			glBindAttribLocation(handle, i, attributeNames_[i]);
		}
		checkGLError("glBindAttribLocation");

		glLinkProgram(handle);
		checkGLError("glLinkProgram");

		GLint linkStatus = GL_FALSE;
		glGetProgramiv(handle, GL_LINK_STATUS, &linkStatus);
		if(linkStatus != GL_TRUE)
		{
			GLint bufLength = 0;
			glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &bufLength);
			if(bufLength)
			{
				Vector<char> buf;
				buf.resize(bufLength);
			
				glGetProgramInfoLog(handle, bufLength, NULL, &buf[0]);
				debug("Could not link program:\n%s\n", &buf[0]);
			}

			deleteShaderProgram();
			return false;
		}
	}
	else
	{
		deleteShaderProgram();
		return false;
	}

	prepareAttributeBinding();

	prepareUniformBinding();

	return true;
}

unsigned int GXShaderProgram::createShader(unsigned int shaderType_, const char *pSource_)
{
	unsigned int shader = glCreateShader(shaderType_);
	checkGLError("glCreateShader");

	if(shader)
	{
		glShaderSource(shader, 1, &pSource_, NULL);
		checkGLError("glShaderSource");

		glCompileShader(shader);
		checkGLError("glCompileShader");
	
		int compiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if(!compiled)
		{
			int infoLen = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
			if(infoLen)
			{
				Vector<char> buf;
				buf.resize(infoLen);

				glGetShaderInfoLog(shader, infoLen, NULL, &buf[0]);
				debug("Could not compile shader %d:\n%s\n", shaderType_, &buf[0]);
			}

			glDeleteShader(shader);
			shader = 0;
		}
	}

	return shader;
}

void GXShaderProgram::deleteShaderProgram()
{
	if(handle)
	{
		if(vertexShaderHandle)
		{
			glDeleteShader(vertexShaderHandle);
			checkGLError("glDeleteShader");
			vertexShaderHandle = 0;
		}
		if(pixelShaderHandle)
		{
			glDeleteShader(pixelShaderHandle);
			checkGLError("glDeleteShader");
			pixelShaderHandle = 0;
		}

		glDeleteProgram(handle);
		checkGLError("glDeleteProgram");
		handle = 0;
	}
}

void GXShaderProgram::prepareAttributeBinding()
{
	Vector<char> buffer;

	int numAttribs      = 0;
	int maxAttribLength = 0;
	glGetProgramiv(handle, GL_ACTIVE_ATTRIBUTES, 		   &numAttribs     );
	glGetProgramiv(handle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxAttribLength);
	buffer.resize(maxAttribLength+1);

	attributes.resize(numAttribs);
	
	for(int i=0; i<attributes.length(); i++)
	{
		int attribLength;

		int attribLocation;
		unsigned int attribType;
		int attributeArraySize;
		glGetActiveAttrib(handle, i, maxAttribLength, &attribLength, &attributeArraySize, &attribType, &buffer[0]);
		attribLocation			= glGetAttribLocation(handle, &buffer[0]);
		
		attributes[i].construct(attribLocation, findAttributeType(attribType), &buffer[0], attributeArraySize, "");
	}
}

void GXShaderProgram::prepareUniformBinding()
{
	Vector<char> buffer;

	int numUniforms      = 0;
	int maxUniformLength = 0;
	glGetProgramiv(handle, GL_ACTIVE_UNIFORMS          , &numUniforms     );
	glGetProgramiv(handle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxUniformLength);
	buffer.resize(maxUniformLength+1);

	uniforms.resize(numUniforms);
	
	for(int i=0; i<uniforms.length(); i++)
	{
		int uniformLocation;

		int uniformLength;
		unsigned int uniformType;
		int uniformArraySize;
		glGetActiveUniform(handle, i, maxUniformLength, &uniformLength, &uniformArraySize, &uniformType, &buffer[0]);
		uniformLocation		= glGetUniformLocation(handle, &buffer[0]);

		String name = &buffer[0];
		//if(name=="boneMatrices")
		//	name+="[0]";
		int bracketPos = name.find('[');
		if(bracketPos>0)
			name = name.extract(0, bracketPos-1);
		
		uniforms[i].construct(uniformLocation, findUniformType(uniformType), name, uniformArraySize, "");
	}
}

GXShaderAttributeType GXShaderProgram::findAttributeType(int type_) const
{
	switch(type_)
	{
		default:
		case GL_BOOL:
			return GXShaderAttributeType::BOOL;
		case GL_BOOL_VEC2:
			return GXShaderAttributeType::BVEC2;
		case GL_BOOL_VEC3:
			return GXShaderAttributeType::BVEC3;
		case GL_BOOL_VEC4:
			return GXShaderAttributeType::BVEC4;
		case GL_INT:
			return GXShaderAttributeType::INT;
		case GL_INT_VEC2:
			return GXShaderAttributeType::IVEC2;
		case GL_INT_VEC3:
			return GXShaderAttributeType::IVEC3;
		case GL_INT_VEC4:
			return GXShaderAttributeType::IVEC4;
		case GL_FLOAT:
			return GXShaderAttributeType::FLOAT;
		case GL_FLOAT_VEC2:
			return GXShaderAttributeType::VEC2;
		case GL_FLOAT_VEC3:
			return GXShaderAttributeType::VEC3;
		case GL_FLOAT_VEC4:
			return GXShaderAttributeType::VEC4;
		case GL_FLOAT_MAT2:
			return GXShaderAttributeType::MAT2;
		case GL_FLOAT_MAT3:
			return GXShaderAttributeType::MAT3;
		case GL_FLOAT_MAT4:
			return GXShaderAttributeType::MAT4;
	};
}

GXShaderUniformType GXShaderProgram::findUniformType(int type_) const
{
	switch(type_)
	{
		default:
		case GL_BOOL:
			return GXShaderUniformType::BOOL;
		case GL_BOOL_VEC2:
			return GXShaderUniformType::BVEC2;
		case GL_BOOL_VEC3:
			return GXShaderUniformType::BVEC3;
		case GL_BOOL_VEC4:
			return GXShaderUniformType::BVEC4;
		case GL_INT:
			return GXShaderUniformType::INT;
		case GL_INT_VEC2:
			return GXShaderUniformType::IVEC2;
		case GL_INT_VEC3:
			return GXShaderUniformType::IVEC3;
		case GL_INT_VEC4:
			return GXShaderUniformType::IVEC4;
		case GL_FLOAT:
			return GXShaderUniformType::FLOAT;
		case GL_FLOAT_VEC2:
			return GXShaderUniformType::VEC2;
		case GL_FLOAT_VEC3:
			return GXShaderUniformType::VEC3;
		case GL_FLOAT_VEC4:
			return GXShaderUniformType::VEC4;
		case GL_FLOAT_MAT2:
			return GXShaderUniformType::MAT2;
		case GL_FLOAT_MAT3:
			return GXShaderUniformType::MAT3;
		case GL_FLOAT_MAT4:
			return GXShaderUniformType::MAT4;
		case GL_SAMPLER_2D:
			return GXShaderUniformType::SAMPLER2D;
		case GL_SAMPLER_CUBE:
			return GXShaderUniformType::SAMPLERCUBE;
	};
}