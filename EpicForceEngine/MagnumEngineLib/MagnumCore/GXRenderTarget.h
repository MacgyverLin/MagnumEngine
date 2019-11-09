#ifndef _GXRenderTarget_h_
#define _GXRenderTarget_h_

#include "GXDef.h"
#include "GXColorBuffer.h"
#include "GXDepthBuffer.h"
#include "GXTexture2D.h"
#include "GXTextureCube.h"

namespace Magnum
{

class GXRenderTarget
{
private:
	GXRenderTarget(const GXRenderTarget &GXRenderTarget_);
	GXRenderTarget &operator = (const GXRenderTarget &GXRenderTarget_);
public:
	GXRenderTarget(GXColorBuffer *buffer_);

	GXRenderTarget(GXDepthBuffer *buffer_);
		
	GXRenderTarget(GXTexture2D *texture_, int level_);

	GXRenderTarget(GXTextureCube *texture_, int level_, const GXTextureCubeFace &cubeFace_);

	void set(GXColorBuffer *buffer_);

	void set(GXDepthBuffer *buffer_);
	
	void set(GXTexture2D *texture_, int level_);

	void set(GXTextureCube *texture_, int level_, const GXTextureCubeFace &cubeFace_);
private:
	GXPixelBuffer		*buffer;
	int					level;
	GXTextureCubeFace	cubeFace;
};

};

#endif