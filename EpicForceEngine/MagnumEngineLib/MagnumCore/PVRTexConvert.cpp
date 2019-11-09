///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "PVRTexConvert.h"
#include "OutputStream.h"
#include "Array.h"
using namespace Magnum;

#ifdef ENABLE_RESOURCE_IMPORT

#include <PVRTexLib.h>
using namespace pvrtexlib;

#include <IL\il.h>
#include <IL\ilu.h>

unsigned int PVRTexConvert::getPixelType(PrecisionOption precision, AlphaOption alpha, ChromeOption chrome, CompressOption compress, int quality)
{
	if(precision==PO_LDR)
	{
		if(chrome==CO_COLOR)
		{
			if(compress==CO_COMPRESS)
			{
				if(quality==0)
					return ETC_RGB_4BPP;
				else if(quality==1)
					return OGL_PVRTC2;
				else ///if(quality==2)
					return OGL_PVRTC4;
			}
			else //if(compress==CO_NO_COMPRESS)
			{
				if(alpha==AO_GRADIENT)
				{
					if(quality==0)
						return OGL_RGBA_4444;
					else if(quality==1)
						return OGL_RGBA_5551;
					else ///if(quality==2)
						return OGL_RGBA_8888;
				}
				else //if(alpha==AO_NONE)
				{
					if(quality==0)
						return OGL_RGB_565;
					else ///if(quality==2)
						return OGL_RGB_888;
					/*
					if(quality==0)
						return OGL_RGB_555;
					else if(quality==1)
						return OGL_RGB_565;
					else ///if(quality==2)
						return OGL_RGB_888;
					*/
				}
			}
		}
		else if(chrome==CO_GRAYSCALE)
		{
			if(alpha==AO_GRADIENT)
			{
				return OGL_AI_88;
			}
			else //if(alpha==AO_NONE)
			{
				return OGL_I_8;
			}
		}
		else //if(chrome==CO_NONE)
		{
			if(alpha==AO_GRADIENT)
			{
				return OGL_A_8;
			}
			else //if(alpha==AO_NONE)
			{
				return OGL_A_8;
			}
		}
	}
	else // if(precision==PO_HDR)
	{
		if(quality==0)
			return D3D_ABGR_16161616F;
		else // if(quality==1)
			return D3D_ABGR_32323232F;
	}
}

unsigned int PVRTexConvert::getConvertFormat(unsigned int pixelType)
{
	if(pixelType==OGL_RGBA_4444)                    return IL_RGBA;
	else if(pixelType==OGL_RGBA_5551)				return IL_RGBA;
	else if(pixelType==OGL_RGBA_8888)				return IL_RGBA;
												  
	else if(pixelType==OGL_RGB_555)					return IL_RGB;
	else if(pixelType==OGL_RGB_565)					return IL_RGB;
	else if(pixelType==OGL_RGB_888)					return IL_RGB;
												  
	else if(pixelType==ETC_RGB_4BPP)				return IL_RGBA;
	else if(pixelType==OGL_PVRTC2)					return IL_RGBA;
	else if(pixelType==OGL_PVRTC4)					return IL_RGBA;
												  
	else if(pixelType==D3D_ABGR_16161616F)			return IL_RGBA;
	else if(pixelType==D3D_ABGR_32323232F)			return IL_RGBA;
												  
	else if(pixelType==OGL_I_8)						return IL_LUMINANCE;
	else if(pixelType==OGL_AI_88)					return IL_LUMINANCE_ALPHA;
	else// if(pixelType==OGL_A_8)					
		return IL_ALPHA;
}

unsigned int PVRTexConvert::getConvertPixelType(unsigned int pixelType)
{
	if(pixelType==OGL_RGBA_4444)                    return IL_UNSIGNED_BYTE;	
	else if(pixelType==OGL_RGBA_5551)				return IL_UNSIGNED_BYTE;	
	else if(pixelType==OGL_RGBA_8888)				return IL_UNSIGNED_BYTE;	

	else if(pixelType==OGL_RGB_555)					return IL_UNSIGNED_BYTE;	
	else if(pixelType==OGL_RGB_565)					return IL_UNSIGNED_BYTE;	
	else if(pixelType==OGL_RGB_888)					return IL_UNSIGNED_BYTE;	

	else if(pixelType==ETC_RGB_4BPP)				return IL_UNSIGNED_BYTE;	
	else if(pixelType==OGL_PVRTC2)					return IL_UNSIGNED_BYTE;	
	else if(pixelType==OGL_PVRTC4)					return IL_UNSIGNED_BYTE;	

	else if(pixelType==D3D_ABGR_16161616F)			return IL_UNSIGNED_SHORT;
	else if(pixelType==D3D_ABGR_32323232F)			return IL_UNSIGNED_INT;	

	else if(pixelType==OGL_I_8)						return IL_UNSIGNED_BYTE;	
	else if(pixelType==OGL_AI_88)					return IL_UNSIGNED_BYTE;	
	else// if(pixelType==OGL_A_8)					
		return IL_UNSIGNED_BYTE;	
}

void PVRTexConvert::convertToRGBA4444(Vector<unsigned char> &buf)
{
	unsigned short *pixel = (unsigned short *)(&buf[0]);
	for(int i=0; i<buf.length(); i+=4)
	{
		unsigned char r = buf[i+0];
		unsigned char g = buf[i+1];
		unsigned char b = buf[i+2];
		unsigned char a = buf[i+3];
		
		*pixel++ = ((r>>4)<<12) | ((g>>4)<<8) | ((b>>4)<<4) | ((a>>4)   );
	}
}

void PVRTexConvert::convertToRGBA5551(Vector<unsigned char> &buf)
{
	unsigned short *pixel = (unsigned short *)(&buf[0]);
	for(int i=0; i<buf.length(); i+=4)
	{
		unsigned char r = buf[i+0];
		unsigned char g = buf[i+1];
		unsigned char b = buf[i+2];
		unsigned char a = buf[i+3];

		*pixel++ = ( ((r>>3)<<11) | ((g>>3)<<6) | ((b>>3)<<1) | (a==255?1:0)   );
	}
}

void PVRTexConvert::convertToRGB555(Vector<unsigned char> &buf)
{
	unsigned short *pixel = (unsigned short *)(&buf[0]);
	for(int i=0; i<buf.length(); i+=4)
	{
		unsigned char r = buf[i+0];
		unsigned char g = buf[i+1];
		unsigned char b = buf[i+2];

		*pixel++ = ((r>>3)<<10) | ((g>>3)<<5) | ((b>>3)   );
	}
}

void PVRTexConvert::convertToRGB565(Vector<unsigned char> &buf)
{
	unsigned short *pixel = (unsigned short *)(&buf[0]);
	for(int i=0; i<buf.length(); i+=4)
	{
		unsigned char r = buf[i+0];
		unsigned char g = buf[i+1];
		unsigned char b = buf[i+2];

		*pixel++ = ((r>>3)<<11) | ((g>>2)<<5) | ((b>>3)   );
	}
}

void PVRTexConvert::convertToRGB888(Vector<unsigned char> &buf)
{
	unsigned char *pixel = (unsigned char *)(&buf[0]);
	for(int i=0; i<buf.length(); i+=4)
	{
		unsigned char r = buf[i+0];
		unsigned char g = buf[i+1];
		unsigned char b = buf[i+2];
	
		*pixel++ = r;
		*pixel++ = g;
		*pixel++ = b;
	}
}

void PVRTexConvert::convertToAI88(Vector<unsigned char> &buf)
{
	unsigned char *pixel = (unsigned char *)(&buf[0]);
	for(int i=0; i<buf.length(); i+=4)
	{
		unsigned char r = buf[i+0];
		unsigned char g = buf[i+1];
		unsigned char b = buf[i+2];
		unsigned char a = buf[i+3];

		unsigned char intensity = r*0.2989f + g*0.5870f + b*0.1140f;
		*pixel++ = intensity;
		*pixel++ = a;
	}
}

void PVRTexConvert::convertToI8(Vector<unsigned char> &buf)
{
	unsigned char *pixel = (unsigned char *)(&buf[0]);
	for(int i=0; i<buf.length(); i+=4)
	{
		unsigned char r = buf[i+0];
		unsigned char g = buf[i+1];
		unsigned char b = buf[i+2];
		unsigned char a = buf[i+3];

		unsigned char intensity = r*0.2989f + g*0.5870f + b*0.1140f;
		*pixel++ = intensity;
	}
}

void PVRTexConvert::convertToA8(Vector<unsigned char> &buf)
{
	unsigned char *pixel = (unsigned char *)(&buf[0]);
	for(int i=0; i<buf.length(); i+=4)
	{
		unsigned char r = buf[i+0];
		unsigned char g = buf[i+1];
		unsigned char b = buf[i+2];
		unsigned char a = buf[i+3];

		*pixel++ = a;
	}
}

void *PVRTexConvert::makePVRTexture(const void *textureBuf, 
								    int topLevelMipmapWidth, int topLevelMipmapHeight, 
									int numMipMaps,	int numSurfaces, 
									bool cubemap, bool volumeTexture, 
									unsigned int pixelType)
{
	PVRTRY
	{
		// get the utilities instance
		PVRTextureUtilities sPVRU = PVRTextureUtilities();
		// make a CPVRTexture instance with data passed
	
		unsigned int pt = pixelType;
		if(pixelType==ETC_RGB_4BPP || pixelType==OGL_PVRTC2 || pixelType==OGL_PVRTC4)
			pt = eInt8StandardPixelType;

		CPVRTexture *orginalTexture = new CPVRTexture(
			topLevelMipmapWidth,	// u32Width,
			topLevelMipmapHeight,	// u32Height,
			numMipMaps,				// u32MipMapCount,
			numSurfaces,			// u32NumSurfaces,
			false,					// bBorder,
			false,					// bTwiddled,
			cubemap,				// bCubeMap,
			volumeTexture,			// bVolume,
			false,					// bFalseMips,
			true,					// bHasAlpha
			false,					// bVerticallyFlipped
			(PixelType)pt,			// ePixelType, 
			0.0f,					// fNormalMap,
			(unsigned char *)textureBuf				// pPixelData
			);
		assert(orginalTexture);


		if(pixelType==ETC_RGB_4BPP || pixelType==OGL_PVRTC2 || pixelType==OGL_PVRTC4)
		{
			CPVRTextureHeader sProcessHeader(orginalTexture->getHeader());
			//sProcessHeader.setMipMapCount(8);
			//sProcessHeader.setNormalMap(5.0f);
			//sProcessHeader.setFalseMips(true);
		
			sPVRU.ProcessRawPVR(*orginalTexture, sProcessHeader);
		
			CPVRTexture *compressedTexture = new CPVRTexture(orginalTexture->getHeader());
			compressedTexture->setPixelType((PixelType)pixelType);

			sPVRU.CompressPVR(*orginalTexture, *compressedTexture);
		
			delete orginalTexture;

			return compressedTexture;
		}
		else
		{
			return orginalTexture;
			//return writeTexture(filename, &sOriginalTexture);
		}
	}
	PVRCATCH(myException)
	{
		// handle any exceptions here
		debug("Exception compiling texture assets: %s", myException.what() );
		assert(0);

		return 0;
	}
}

#endif