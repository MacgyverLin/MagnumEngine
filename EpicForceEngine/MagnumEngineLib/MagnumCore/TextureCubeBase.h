///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _TextureCubeBase_h_
#define _TextureCubeBase_h_

#include "Stage.h"
#include "Video.h"
#include "TextureBase.h"
using namespace Magnum;

namespace Magnum
{

/**
* TextureCubeBase. This is the base class for all Cubemap Texture
* @see TextureBase
*/
class TextureCubeBase : public TextureBase
{
public:
	/**
	* TextureCubeBase Constructor.
	* To Construct the TextureCubeBase
	*/
	TextureCubeBase();

	/**
	* TextureCubeBase Destructor.
	* To Destruct the TextureCubeBase for the owner.
	*/
	virtual ~TextureCubeBase();
protected:
private:
};

};

#endif
