#ifndef _GXTexture2D_h_
#define _GXTexture2D_h_

#include "GXDef.h"
#include "GXTexture.h"

namespace Magnum
{

/**
* GXTexture2D encapsulate a 2D Texture of Graphics Device. This is a Base Class of all other 2D Texture
*/
class GXTexture2D : public GXTexture
{
friend class GXContext;
private:
	GXTexture2D(const GXTexture2D &texture2D_);
	GXTexture2D &operator = (const GXTexture2D &texture2D_);
public:
	GXTexture2D(int width_, int height_, const GXPixelFormat &format_, const GXPixelBufferOption &option_ = GXPixelBufferOption::None);
	
	GXTexture2D(const char *fileName_);

	GXTexture2D(const char *fileImage_, unsigned int length_);

	virtual ~GXTexture2D();
	
	void setPixels(int level_, const Vector<unsigned char> &pixels_);
	
	void setPixels(int level_, const Vector<unsigned char> &pixels_, int dx_, int dy_, int dw_, int dh_);
	
	void setPixels(int level_, const Vector<unsigned char> &pixels_, int offset_, int pitch_);

	void setPixels(int level_, const Vector<unsigned char> &pixels_, const GXPixelFormat &format_);
	
	void setPixels(int level_, const Vector<unsigned char> &pixels, const GXPixelFormat &format_, 
		           int offset_, int pitch_, int dx_, int dy_, int dw_, int dh_);

	void generateMipmap();
};

};

#endif