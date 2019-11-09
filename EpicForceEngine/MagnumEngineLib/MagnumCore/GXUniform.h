#ifndef _GXUniform_h_
#define _GXUniform_h_

#include "GXDef.h"

namespace Magnum
{

/**
* GXUniform encapsulate a Shader UNiform of Graphics Device. 
*/
class GXUniform
{
friend class GXShaderProgram;
public:
	GXUniform();

	~GXUniform();

	GXUniform &operator = (const GXUniform &other);

	void construct(int location_, const GXShaderUniformType &type_, const char *name_, int arraySize_, const char *semantic_);

	void copyValue(const GXUniform &other);

	template <class T>
	void setValue(const T &values_, int count_ = 1, int offset_ = 0)
	{
		assert(sizeof(T)*(offset_+count_)<=buffer.length());
		const T *bufferPtr = (const T *)(&buffer[0]); 

		invalid			= true;

		System::memcpy((void *)(&bufferPtr[offset_]), &values_, sizeof(T)*(count_) );
	}
	 
	template <class T>
	void getValue(T &values_, int count_ = 1, int offset_ = 0)
	{
		assert(sizeof(T)*(offset_+count_)<=buffer.length()); 
		const T *bufferPtr = (const T *)(&buffer[0]); 

		System::memcpy(&values_, (void *)(&bufferPtr[offset_]), sizeof(T)*(count_) );
	}

	int	getLocation() const;

	const GXShaderUniformType &getType() const;

	const char *getName() const;
	 
	int getArraySize() const;

	const char *getSemantic() const;

	void read(InputStream &is);

	void write(OutputStream &os) const;
private:
	bool				invalid;

	int					location;
	GXShaderUniformType type;
	String				name;
	int					arraySize;
	String				semantic;

	Vector<char>		buffer;
};

};

#endif