#ifndef _GXAttribute_h_
#define _GXAttribute_h_

#include "GXDef.h"

namespace Magnum
{

/**
* GXBlendState encapsulate a Vertex Attribute of Graphics Device
*/
class GXAttribute
{
friend class GXShaderProgram;
public:
	GXAttribute();

	~GXAttribute();

	void construct(int location_, const GXShaderAttributeType &type_, const char *name_, int arraySize_, const char *semantic_);

	int	getLocation() const;

	const GXShaderAttributeType &getType() const;

	const char *getName() const;

	int getArraySize() const;

	const char *getSemantic() const;
private:
	int							location;
	GXShaderAttributeType		type;
	String						name;
	int							arraySize;
	String						semantic;
};

};

#endif