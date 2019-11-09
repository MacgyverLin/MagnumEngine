///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _Texture2DBase_h_
#define _Texture2DBase_h_

#include "Stage.h"
#include "Video.h"
#include "TextureBase.h"
using namespace Magnum;

namespace Magnum
{

/**
* TextureBase. This is the base class for all 2D Texture
* @see TextureBase
*/
class Texture2DBase : public TextureBase
{
public:
	/**
	* Texture2DBase Constructor.
	* To Construct the Texture2DBase
	*/
	Texture2DBase();

	/**
	* TextureBase Destructor.
	* To Destruct the TextureBase for the owner.
	*/
	virtual ~Texture2DBase();
protected:
private:
};

};

#endif
