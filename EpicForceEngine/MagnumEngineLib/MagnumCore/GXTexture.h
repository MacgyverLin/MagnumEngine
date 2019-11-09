#ifndef _GXTexture_h_
#define _GXTexture_h_

#include "GXDef.h"
#include "GXPixelBuffer.h"
#include "GXTextureFilterState.h"
#include "GXTextureWrapState.h"
#include "FileIO.h"

namespace Magnum
{

/**
* GXTexture encapsulate a Texture of Graphics Device. This is a Base Class of all other Texture
*/
class GXTexture : public GXPixelBuffer
{
friend class GXContext;
private:
	GXTexture(const GXTexture &texture);
	GXTexture &operator = (const GXTexture &texture);
public:
	GXTexture(const GXPixelBufferType &type_, int width_, int height_, const GXPixelFormat &format_, const GXPixelBufferOption &option_);
	
	GXTexture(const GXPixelBufferType &type_, const char *fileName_);
	
	GXTexture(const GXPixelBufferType &type_, const char *fileImage_, unsigned int length_);

	virtual ~GXTexture();
	
	const GXTextureFilterState &getFilter() const;

	void setFilter(const GXTextureFilterState &filter_);

	void setFilter(const GXTextureMagFilterMode &mag_, const GXTextureMinFilterMode &min_);

	const GXTextureWrapState &getWrap() const;

	void setWrap(const GXTextureWrapState &wrap_);

	void setWrap(const GXTextureWrapMode &mode_);
	
	void setWrap(const GXTextureWrapMode &wrapS_, const GXTextureWrapMode &wrapT_);

	float getMaxAnisotropy() const;
	
	void setMaxAnisotropy(float anisotropy_);
protected:
	GXTextureFilterState	filter;
	GXTextureWrapState		wrap;
	float					maxAnisotropy;
};

};

#endif