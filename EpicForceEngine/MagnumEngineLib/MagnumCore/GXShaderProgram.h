#ifndef _GXShaderProgram_h_
#define _GXShaderProgram_h_

#include "GXDef.h"
#include "GXAttribute.h"
#include "GXUniform.h"

namespace Magnum
{

/**
* GXPrimitive encapsulate a Shader Program of Graphics Device
*/
class GXShaderProgram
{
friend class GXContext;
private:
	GXShaderProgram(const GXShaderProgram &GXShaderProgram_);
	GXShaderProgram &operator = (const GXShaderProgram &GXShaderProgram_);
public:
	GXShaderProgram(const char *vpFileName_, const char *fpFileName_,
					const Vector<String> &attributeNames_);

	GXShaderProgram(const char *vpFileImage_, unsigned int vpFileImagelength_, 
		            const char *fpFileImage_, unsigned int fpFileImagelength_,
					const Vector<String> &attributeNames_);

	virtual ~GXShaderProgram();

	int getUniformArraySize(int i_) const;

	int getAttributeCount() const;

	int getAttributeIdx(const char *name_) const;

	int getAttributeLocation(int i_) const;

	const GXShaderAttributeType &getAttributeType(int i_) const;

	const char *getAttributeName(int i_) const;

	const char *getAttributeSemantic(int i_) const;

	int getAttributeArraySize(int i_) const;

	int getUniformCount() const;

	int getUniformIdx(const char *name_) const;

	/*
	const char *getUniformBinding(int index) const

	void setUniformBinding(int index, const char *name)

	const char *getAttributeBinding(int index) const

	void setAttributeBinding(int index, const char *name)
	*/

	int getUniformLocation(int i_) const;

	const GXShaderUniformType &getUniformType(int i_) const;

	const char *getUniformName(int i_) const;

	const char *getUniformSemantic(int i_) const;

	void copyUniformValue(int i_, const GXUniform &other)
	{
		uniforms[i_].copyValue(other);
	};

	template <class T>
	void setUniformValue(int i_, const T &value_, int count_ = 1, int offset_ = 0)
	{
		assert( i_ < uniforms.length() );
		assert( sizeof(T)==uniforms[i_].type.getSize() );

		uniforms[i_].setValue(value_, count_, offset_);

		invalid = true;
	}

	bool								invalid;

	unsigned int						handle;
	unsigned int						vertexShaderHandle;
	unsigned int						pixelShaderHandle;

	Vector<GXAttribute>					attributes;
	Vector<GXUniform>					uniforms;

	void update();
private:
	bool createShaderProgram(const char *pVertexSource, const char *pFragmentSource,
							 const Vector<String> &attributeNames_);

	unsigned int createShader(unsigned int shaderType, const char *pSource);

	void deleteShaderProgram();

	void prepareAttributeBinding();

	void prepareUniformBinding();

	GXShaderAttributeType findAttributeType(int type) const;

	GXShaderUniformType findUniformType(int type) const;
public:
	static void uniformBool(const GXUniform &uniform);
	static void uniformBVec2(const GXUniform &uniform);
	static void uniformBVec3(const GXUniform &uniform);
	static void uniformBVec4(const GXUniform &uniform);
	static void uniformInt(const GXUniform &uniform);
	static void uniformIVec2(const GXUniform &uniform);
	static void uniformIVec3(const GXUniform &uniform);
	static void uniformIVec4(const GXUniform &uniform);
	static void uniformFloat(const GXUniform &uniform);
	static void uniformVec2(const GXUniform &uniform);
	static void uniformVec3(const GXUniform &uniform);
	static void uniformVec4(const GXUniform &uniform);
	static void uniformMat2(const GXUniform &uniform);
	static void uniformMat3(const GXUniform &uniform);
	static void uniformMat4(const GXUniform &uniform);
	static void uniformSampler2D(const GXUniform &uniform);
	static void uniformSamplerCube(const GXUniform &uniform);
};

};

#endif