///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _PVRTexConvert_h_
#define _PVRTexConvert_h_

#include "Stage.h"
#include "Array.h"
#include "InputStream.h"
#include "OutputStream.h"

#ifdef ENABLE_RESOURCE_IMPORT

namespace Magnum
{

class PVRTexConvert
{
public:
	enum PrecisionOption
	{
		PO_HDR,
		PO_LDR
	};

	enum AlphaOption
	{
		AO_GRADIENT,
		AO_NONE
	};

	enum ChromeOption
	{
		CO_COLOR,
		CO_GRAYSCALE,
		CO_NONE,
	};

	enum CompressOption
	{
		CO_COMPRESS,
		CO_NO_COMPRESS,
	};
	static unsigned int getPixelType(PrecisionOption precision, AlphaOption alpha, ChromeOption chrome, CompressOption compress, int quality);
	static unsigned int getConvertPixelType(unsigned int pixelType);
	static unsigned int getConvertFormat(unsigned int pixelType);

	static void convertToRGBA4444(Vector<unsigned char> &buf);
	static void convertToRGBA5551(Vector<unsigned char> &buf);
	static void convertToRGB555(Vector<unsigned char> &buf);
	static void convertToRGB565(Vector<unsigned char> &buf);
	static void convertToRGB888(Vector<unsigned char> &buf);
	static void convertToAI88(Vector<unsigned char> &buf);
	static void convertToI8(Vector<unsigned char> &buf);
	static void convertToA8(Vector<unsigned char> &buf);

	static void *makePVRTexture(const void *textureBuf, 
								int topLevelMipmapWidth, int topLevelMipmapHeight, 
								int numMipMaps,	int numSurfaces,
								bool cubemap, bool volumeTexture, 
								unsigned int pixelType);
};

}

#endif

#endif
