#ifndef _GXTextureCube_h_
#define _GXTextureCube_h_

#include "GXDef.h"
#include "GXTexture.h"

namespace Magnum
{

/**
* GXTextureCube encapsulate a Cube Map Texture of Graphics Device. This is a Base Class of all other CubeMap Texture
*/
class GXTextureCube : public GXTexture
{
friend class GXContext;
private:
	GXTextureCube(const GXTextureCube &textureCube_);
	GXTextureCube &operator = (const GXTextureCube &textureCube_);
public:
	GXTextureCube(int width_, const GXPixelFormat &format_, const GXPixelBufferOption &option_ = GXPixelBufferOption::None);

	GXTextureCube(const char *fileName_);
	
	GXTextureCube(const char *fileImage_, unsigned int length_);

	virtual ~GXTextureCube();

	void setPixels(int level_, const GXTextureCubeFace &cubeFace_, const Vector<unsigned char> &pixels_);

	void setPixels(int level_, const GXTextureCubeFace &cubeFace_, const Vector<unsigned char> &pixels_, 
		           int dx_, int dy_, int dw_, int dh_);
	
	void setPixels(int level_, const GXTextureCubeFace &cubeFace_, const Vector<unsigned char> &pixels_, 
		           int offset_, int pitch_);

	void setPixels(int level_, const GXTextureCubeFace &cubeFace_, const Vector<unsigned char> &pixels_, 
		           const GXPixelFormat &format);
		
	void setPixels(int level_, const GXTextureCubeFace &cubeFace_, const Vector<unsigned char> &pixels_, 
		           const GXPixelFormat &format_, 
		           int offset_, int pitch_,
				   int dx_, int dy_, int dw_, int dh_);

	void generateMipmap();
};

};

#endif