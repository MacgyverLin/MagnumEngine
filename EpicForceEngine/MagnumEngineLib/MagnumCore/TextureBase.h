///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _TextureBase_h_
#define _TextureBase_h_

#include "Stage.h"
#include "Video.h"
#include "Component.h"
#include "GXTextureFilterState.h"
#include "GXTextureWrapState.h"
using namespace Magnum;

namespace Magnum
{

/**
* TextureBase. This is the base class for all Texture
*/
class TextureBase
{
public:
	/**
	* TextureBase Constructor.
	* To Construct the TextureBase
	*/
	TextureBase();

	/**
	* TextureBase Destructor.
	* To Destruct the TextureBase for the owner.
	*/
	virtual ~TextureBase();

	/**
	* Get the Handle of the Texture. This is a pure virtual function all sub classes should implemented this function
	* @return void *, handle of the texture
	*/
	virtual void *getHandle() const = 0;

	/**
	* Get the Width of the Texture. This is a pure virtual function all sub classes should implemented this function
	* @return int, the Width of the Texture.
	*/
	virtual int getWidth() const = 0;

	/**
	* Get the Height of the Texture. This is a pure virtual function all sub classes should implemented this function
	* @return int, the Height of the Texture.
	*/
	virtual int getHeight() const = 0;

	/**
	* Get the Mipmap Level Count of the Texture. This is a pure virtual function all sub classes should implemented this function
	* @return int, the Mipmap Level Count of the Texture.
	*/
	virtual int getLevelCount() const = 0;

	/**
	* Check if texture is renderable. This is a pure virtual function all sub classes should implemented this function
	* @return true if the Texture is Renderable.
	*/
	virtual bool isRenderable() const = 0;

	/**
	* Check if texture is power of 2 in both width and height. This is a pure virtual function all sub classes should implemented this function
	* @return true if the Texture is power of 2.
	*/
	virtual bool isPowerOfTwo() const = 0;

	/**
	* Set the Minification Filter of the Texture. 
	* @param minFilter_, GXTextureMinFilterMode, the Minification Filter of the Texture
	* @see GXTextureMinFilterMode
	*/
	void setMinFilterMode(const GXTextureMinFilterMode &minFilter_);

	/**
	* Set the Magification Filter of the Texture.
	* @param magFilter_, GXTextureMagFilterMode, the Magification Filter of the Texture
	* @see GXTextureMagFilterMode
	*/
	void setMagFilterMode(const GXTextureMagFilterMode &magFilter_);

	/**
	* Get the Minification Filter of the Texture.
	* @return GXTextureMinFilterMode, the Minification Filter of the Texture
	* @see GXTextureMinFilterMode
	*/
	const GXTextureMinFilterMode &getMinFilterMode() const;

	/**
	* Get the Magification Filter of the Texture.
	* @return GXTextureMagFilterMode, the Magification Filter of the Texture
	* @see GXTextureMagFilterMode
	*/
	const GXTextureMagFilterMode &getMagFilterMode() const;

	/**
	* Set the Warp Mode of S direction of the Texture
	* @param wrapS_, GXTextureWrapMode, the Warp Mode of S direction of the Texture
	* @see GXTextureWrapMode
	*/
	void setWrapS(const GXTextureWrapMode &wrapS_);

	/**
	* Get the Warp Mode of S direction of the Texture
	* @return, GXTextureWrapMode, the Warp Mode of S direction of the Texture
	* @see GXTextureWrapMode
	*/
	const GXTextureWrapMode &getWrapS() const;

	/**
	* Set the Warp Mode of T direction of the Texture
	* @param wrapT_, GXTextureWrapMode, the Warp Mode of T direction of the Texture
	* @see GXTextureWrapMode
	*/
	void setWrapT(const GXTextureWrapMode &wrapT_);

	/**
	* Get the Warp Mode of T direction of the Texture
	* @return, GXTextureWrapMode, the Warp Mode of T direction of the Texture
	* @see GXTextureWrapMode
	*/
	const GXTextureWrapMode &getWrapT() const;
protected:
private:
	GXTextureFilterState filterState;
	GXTextureWrapState	 wrapState;
};

};

#endif
