#ifndef _GXTextureFilterState_h_
#define _GXTextureFilterState_h_

#include "GXDef.h"

namespace Magnum
{

/**
* GXTextureFilterState encapsulate a Texture Magnification Filter, Minification Filter State of a Texture
*/
class GXTextureFilterState
{
public:
	GXTextureFilterState(const GXTextureMagFilterMode &mag_, const GXTextureMinFilterMode &min_);

	void set(const GXTextureMagFilterMode &mag_, const GXTextureMinFilterMode &min_);

	void setMagFilter(const GXTextureMagFilterMode &mag_);

	const GXTextureMagFilterMode &getMagFilter() const;

	void setMinFilter(const GXTextureMinFilterMode &min_);

	const GXTextureMinFilterMode &getMinFilter() const;
private:
	GXTextureMagFilterMode mag;
	GXTextureMinFilterMode min;
};

};

#endif