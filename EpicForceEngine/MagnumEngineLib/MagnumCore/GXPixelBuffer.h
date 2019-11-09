#ifndef _GXPixelBuffer_h_
#define _GXPixelBuffer_h_

#include "GXDef.h"

namespace Magnum
{

/**
* GXPixelBuffer is the base class of all Buffer of Graphics Devices
*/
class GXPixelBuffer
{
friend class GXContext;
private:
	GXPixelBuffer(const GXPixelBuffer &buffer_);
	GXPixelBuffer &operator = (const GXPixelBuffer &buffer_);
public:
	GXPixelBuffer(const GXPixelBufferType &type_, 
		          int width_, int height_, 
				  const GXPixelFormat &format_, const GXPixelBufferOption &option_);

	GXPixelBuffer();
	
	virtual ~GXPixelBuffer();

	const GXPixelBufferType &getType() const;
	
	const GXPixelBufferOption &getOption() const;
	
	const GXPixelFormat &getFormat() const;
	
	int getWidth() const;
	
	int getHeight() const;
	
	int getLevelCount() const;

	unsigned int getHandle() const;
	
	bool isRenderable() const;
	
	bool isPowerOfTwo() const;

	int getMipmapWidth(int level_) const;
	
	int getMipmapHeight(int level_) const;
	
	static int getMipmapSize(int level_, int levelCount_, int baseSize_);
	
	static bool isPowerOfTwo(int num_);
protected:
	GXPixelBufferType	type;
	int					width;
	int					height;
	GXPixelFormat		format;
	GXPixelBufferOption option;
	int					levelCount;
	unsigned int		handle;
};

};

#endif