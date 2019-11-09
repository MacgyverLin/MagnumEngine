#ifndef _GXFrameBuffer_h_
#define _GXFrameBuffer_h_

#include "GXDef.h"
#include "GXRenderTarget.h"

namespace Magnum
{

/**
* GXColorBuffer encapsulate a the Frame Buffer of Graphics Device
*/
class GXFrameBuffer
{
friend class GXContext;
private:
	GXFrameBuffer(const GXFrameBuffer &GXFrameBuffer_);
	GXFrameBuffer &operator = (const GXFrameBuffer &GXFrameBuffer_);
public:
	GXFrameBuffer();
	
	GXFrameBuffer(int width_, int height_, 
		          const GXPixelFormat &colorFormat_, const GXPixelFormat &depthFormat_,
		          const GXMultiSampleMode &multiSampleMode_);
	
	virtual ~GXFrameBuffer();

	bool getStatus() const;

	int getWidth() const;
		
	int getHeight() const;
		
	float getAspectRatio() const;
		
	const GXImageRect &getRectangle() const;
	
	const GXPixelFormat &getColorFormat() const;
		
	const GXPixelFormat &getDepthFormat() const;
	
	const GXMultiSampleMode &getMultiSampleMode() const;

	const GXRenderTarget *getColorTarget() const;
		
	void setColorTarget(GXRenderTarget *colorTarget_);
		
	const GXRenderTarget *getDepthTarget() const;
		
	void setDepthTarget(GXRenderTarget *depthTarget_);
protected:
	int					handle;
	bool				status;
	GXImageRect			rect;
	GXPixelFormat		colorFormat;
	GXPixelFormat		depthFormat;
	GXMultiSampleMode	multiSampleMode;
	GXRenderTarget		*colorTarget;
	GXRenderTarget		*depthTarget;
};

};

#endif