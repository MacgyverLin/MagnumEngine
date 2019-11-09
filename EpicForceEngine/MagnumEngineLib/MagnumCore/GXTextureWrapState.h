#ifndef _GXTextureWrapState_h_
#define _GXTextureWrapState_h_

#include "GXDef.h"

namespace Magnum
{

/**
* GXTextureWrapState encapsulate a Wrapping State of a Texture
*/
class GXTextureWrapState
{
public:
	GXTextureWrapState(const GXTextureWrapMode &wrapS_, const GXTextureWrapMode &wrapT_);

	void set(const GXTextureWrapMode &wrapS_, const GXTextureWrapMode &wrapT_);

	void setWrapS(const GXTextureWrapMode &wrapS_);

	const GXTextureWrapMode &getWrapS() const;

	void setWrapT(const GXTextureWrapMode &wrapT_);

	const GXTextureWrapMode &getWrapT() const;
private:
	GXTextureWrapMode wrapS;
	GXTextureWrapMode wrapT;
};

};

#endif