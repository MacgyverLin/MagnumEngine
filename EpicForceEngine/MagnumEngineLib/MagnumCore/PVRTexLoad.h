///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#ifndef _PVRTexLoad_h_
#define _PVRTexLoad_h_

#include "Stage.h"
#include "GXDef.h"
#include "gldef.h"

enum PixelType
{
	MGLPT_ARGB_4444 = 0x00,
	MGLPT_ARGB_1555,
	MGLPT_RGB_565,
	MGLPT_RGB_555,
	MGLPT_RGB_888,
	MGLPT_ARGB_8888,
	MGLPT_ARGB_8332,
	MGLPT_I_8,
	MGLPT_AI_88,
	MGLPT_1_BPP,
	MGLPT_VY1UY0,
	MGLPT_Y1VY0U,
	MGLPT_PVRTC2,
	MGLPT_PVRTC4,

	// OpenGL version of pixel types
	OGL_RGBA_4444= 0x10,
	OGL_RGBA_5551,
	OGL_RGBA_8888,
	OGL_RGB_565,
	OGL_RGB_555,
	OGL_RGB_888,
	OGL_I_8,
	OGL_AI_88,
	OGL_PVRTC2,
	OGL_PVRTC4,
	OGL_BGRA_8888,
	OGL_A_8,
	OGL_PVRTCII4,	//Not in use
	OGL_PVRTCII2,	//Not in use

#ifdef _WIN32
	// S3TC Encoding
	D3D_DXT1 = 0x20,
	D3D_DXT2,
	D3D_DXT3,
	D3D_DXT4,
	D3D_DXT5,
#endif

	//RGB Formats
	D3D_RGB_332 
#ifndef _WIN32
	= 0x25
#endif
	,
	D3D_AL_44,
	D3D_LVU_655,
	D3D_XLVU_8888,
	D3D_QWVU_8888,

	//10 bit integer - 2 bit alpha
	D3D_ABGR_2101010,
	D3D_ARGB_2101010,
	D3D_AWVU_2101010,

	//16 bit integers
	D3D_GR_1616,
	D3D_VU_1616,
	D3D_ABGR_16161616,

	//Float Formats
	D3D_R16F,
	D3D_GR_1616F,
	D3D_ABGR_16161616F,

	//32 bits per channel
	D3D_R32F,
	D3D_GR_3232F,
	D3D_ABGR_32323232F,

	// Ericsson
	ETC_RGB_4BPP,
	ETC_RGBA_EXPLICIT,				// unimplemented
	ETC_RGBA_INTERPOLATED,			// unimplemented

	D3D_A8 = 0x40,
	D3D_V8U8,
	D3D_L16,

	D3D_L8,
	D3D_AL_88,

	//Y'UV Colourspace
	D3D_UYVY,
	D3D_YUY2,

	// DX10
	DX10_R32G32B32A32_FLOAT= 0x50,
	DX10_R32G32B32A32_UINT , 
	DX10_R32G32B32A32_SINT,

	DX10_R32G32B32_FLOAT,
	DX10_R32G32B32_UINT,
	DX10_R32G32B32_SINT,

	DX10_R16G16B16A16_FLOAT ,
	DX10_R16G16B16A16_UNORM,
	DX10_R16G16B16A16_UINT ,
	DX10_R16G16B16A16_SNORM ,
	DX10_R16G16B16A16_SINT ,

	DX10_R32G32_FLOAT ,
	DX10_R32G32_UINT ,
	DX10_R32G32_SINT ,

	DX10_R10G10B10A2_UNORM ,
	DX10_R10G10B10A2_UINT ,

	DX10_R11G11B10_FLOAT ,				// unimplemented

	DX10_R8G8B8A8_UNORM , 
	DX10_R8G8B8A8_UNORM_SRGB ,
	DX10_R8G8B8A8_UINT ,
	DX10_R8G8B8A8_SNORM ,
	DX10_R8G8B8A8_SINT ,

	DX10_R16G16_FLOAT , 
	DX10_R16G16_UNORM , 
	DX10_R16G16_UINT , 
	DX10_R16G16_SNORM ,
	DX10_R16G16_SINT ,

	DX10_R32_FLOAT ,
	DX10_R32_UINT ,
	DX10_R32_SINT ,

	DX10_R8G8_UNORM ,
	DX10_R8G8_UINT ,
	DX10_R8G8_SNORM , 
	DX10_R8G8_SINT ,

	DX10_R16_FLOAT ,
	DX10_R16_UNORM ,
	DX10_R16_UINT ,
	DX10_R16_SNORM ,
	DX10_R16_SINT ,

	DX10_R8_UNORM, 
	DX10_R8_UINT,
	DX10_R8_SNORM,
	DX10_R8_SINT,

	DX10_A8_UNORM, 
	DX10_R1_UNORM, 
	DX10_R9G9B9E5_SHAREDEXP,	// unimplemented
	DX10_R8G8_B8G8_UNORM,		// unimplemented
	DX10_G8R8_G8B8_UNORM,		// unimplemented

#ifdef _WIN32
	DX10_BC1_UNORM,	
	DX10_BC1_UNORM_SRGB,

	DX10_BC2_UNORM,	
	DX10_BC2_UNORM_SRGB,

	DX10_BC3_UNORM,	
	DX10_BC3_UNORM_SRGB,

	DX10_BC4_UNORM,				// unimplemented
	DX10_BC4_SNORM,				// unimplemented

	DX10_BC5_UNORM,				// unimplemented
	DX10_BC5_SNORM,				// unimplemented
#endif
	// OpenVG

	/* RGB{A,X} channel ordering */
	ePT_VG_sRGBX_8888  = 0x90,
	ePT_VG_sRGBA_8888,
	ePT_VG_sRGBA_8888_PRE,
	ePT_VG_sRGB_565,
	ePT_VG_sRGBA_5551,
	ePT_VG_sRGBA_4444,
	ePT_VG_sL_8,
	ePT_VG_lRGBX_8888,
	ePT_VG_lRGBA_8888,
	ePT_VG_lRGBA_8888_PRE,
	ePT_VG_lL_8,
	ePT_VG_A_8,
	ePT_VG_BW_1,

	/* {A,X}RGB channel ordering */
	ePT_VG_sXRGB_8888,
	ePT_VG_sARGB_8888,
	ePT_VG_sARGB_8888_PRE,
	ePT_VG_sARGB_1555,
	ePT_VG_sARGB_4444,
	ePT_VG_lXRGB_8888,
	ePT_VG_lARGB_8888,
	ePT_VG_lARGB_8888_PRE,

	/* BGR{A,X} channel ordering */
	ePT_VG_sBGRX_8888,
	ePT_VG_sBGRA_8888,
	ePT_VG_sBGRA_8888_PRE,
	ePT_VG_sBGR_565,
	ePT_VG_sBGRA_5551,
	ePT_VG_sBGRA_4444,
	ePT_VG_lBGRX_8888,
	ePT_VG_lBGRA_8888,
	ePT_VG_lBGRA_8888_PRE,

	/* {A,X}BGR channel ordering */
	ePT_VG_sXBGR_8888,
	ePT_VG_sABGR_8888 ,
	ePT_VG_sABGR_8888_PRE,
	ePT_VG_sABGR_1555,
	ePT_VG_sABGR_4444,
	ePT_VG_lXBGR_8888,
	ePT_VG_lABGR_8888,
	ePT_VG_lABGR_8888_PRE,

	// max cap for iterating
	END_OF_PIXEL_TYPES,

	MGLPT_NOTYPE = 0xffffffff
};

struct PVR_Texture_Header
{
	unsigned int dwHeaderSize;			/*!< size of the structure */
	unsigned int dwHeight;				/*!< height of surface to be created */
	unsigned int dwWidth;				/*!< width of input surface */
	unsigned int dwMipMapCount;			/*!< number of mip-map levels requested */
	unsigned int dwpfFlags;				/*!< pixel format flags */
	unsigned int dwTextureDataSize;		/*!< Total size in bytes */
	unsigned int dwBitCount;			/*!< number of bits per pixel  */
	unsigned int dwRBitMask;			/*!< mask for red bit */
	unsigned int dwGBitMask;			/*!< mask for green bits */
	unsigned int dwBBitMask;			/*!< mask for blue bits */
	unsigned int dwAlphaBitMask;		/*!< mask for alpha channel */
	unsigned int dwPVR;					/*!< magic number identifying pvr file */
	unsigned int dwNumSurfs;			/*!< the number of surfaces present in the pvr */
};

unsigned int PVRTTextureLoadFromPointer(const void* pointer, bool bAllowDecompress, 
										int &width, int &height, GXPixelFormat &format, int &levelCount);

#endif