///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "TextureCubeFile.h"
#include "EString.h"
#include "InputStream.h"
#include "Video.h"
#include "GXTextureCube.h"
using namespace Magnum;

TextureCubeFile::Data::Data()
: version(0)
, platform(Platform::PC)
, textureHandle(0)
{
}

TextureCubeFile::Data::~Data()
{
}

void TextureCubeFile::Data::read(InputStream &is)
{
	is >> version;
	is >> platform;
}

void TextureCubeFile::Data::write(OutputStream &os) const
{
	os << version;
	os << platform;
}

////////////////////////////////////////////////////////////////
TextureCubeFile::Resource::Resource(const char *path_)
: ResourceAccess(path_)
{
}	

TextureCubeFile::Resource::~Resource()
{
	onDestroy();
}

unsigned char *TextureCubeFile::Resource::onCreate(int length_)
{
	buffer.resize(length_);

	return &buffer[0];
}

void TextureCubeFile::Resource::onLoaded()
{
	MemInputStream is(&buffer[0], buffer.length());

	is >> data;
	
	int position = is.tell();
	GXTextureCube *texture = new GXTextureCube((const char *)&buffer[position], buffer.length()-position);
	data.textureHandle = (void *)texture;
	assert(data.textureHandle);

	buffer.destroy();
}

void TextureCubeFile::Resource::onDestroy()
{
	if(data.textureHandle)
	{
		GXTexture *texture = (GXTexture *)data.textureHandle;

		delete texture;
		data.textureHandle = 0;
	}

	buffer.destroy();
}

void *TextureCubeFile::Resource::getHandle() const
{
	return data.textureHandle;
}

int TextureCubeFile::Resource::getWidth() const
{
	assert(data.textureHandle);
	GXTexture *texture = (GXTexture *)data.textureHandle;

	return texture->getWidth();
}

int TextureCubeFile::Resource::getHeight() const
{
	assert(data.textureHandle);
	GXTexture *texture = (GXTexture *)data.textureHandle;

	return texture->getHeight();
}

int TextureCubeFile::Resource::getLevelCount() const
{
	assert(data.textureHandle);
	GXTexture *texture = (GXTexture *)data.textureHandle;

	return texture->getLevelCount();
}

bool TextureCubeFile::Resource::isRenderable() const
{
	assert(data.textureHandle);
	GXTexture *texture = (GXTexture *)data.textureHandle;

	return texture->isRenderable();
}

bool TextureCubeFile::Resource::isPowerOfTwo() const
{
	assert(data.textureHandle);
	GXTexture *texture = (GXTexture *)data.textureHandle;

	return texture->isPowerOfTwo();
}

#ifdef ENABLE_RESOURCE_IMPORT

#include "gldef.h"

#include <IL\il.h>
#include <IL\ilu.h>

#include "PVRTexConvert.h"
#include "PVRTexLib.h"
using namespace pvrtexlib;

TextureCubeFile::ResourceImporter::ResourceImporter(const char *path_)
: ResourceImport(path_)
, precision(PVRTexConvert::PO_LDR)
, alpha(PVRTexConvert::AO_GRADIENT)
, chrome(PVRTexConvert::CO_COLOR)
, compress(PVRTexConvert::CO_NO_COMPRESS)
, quality(2)
{
}

TextureCubeFile::ResourceImporter::~ResourceImporter()
{
}

bool TextureCubeFile::ResourceImporter::initiate()
{
	ilInit();

	return true;
}

void TextureCubeFile::ResourceImporter::terminate()
{
	ilShutDown();
}

bool TextureCubeFile::ResourceImporter::onExportFile(const char *srcFilename_, const char *dstFilename_)
{
	unsigned int 
	//pixelType = PVRTexConvert::getPixelType(PVRTexConvert::PO_HDR, PVRTexConvert::AO_GRADIENT, PVRTexConvert::CO_COLOR, PVRTexConvert::CO_NO_COMPRESS, 0); // D3D_ABGR_16161616F
	//pixelType = PVRTexConvert::getPixelType(PVRTexConvert::PO_HDR, PVRTexConvert::AO_GRADIENT, PVRTexConvert::CO_COLOR, PVRTexConvert::CO_NO_COMPRESS, 1); // D3D_ABGR_32323232F
	//pixelType = PVRTexConvert::getPixelType(PVRTexConvert::PO_LDR, PVRTexConvert::AO_GRADIENT, PVRTexConvert::CO_COLOR, PVRTexConvert::CO_COMPRESS   , 0); // ETC_RGB_4BPP
	//pixelType = PVRTexConvert::getPixelType(PVRTexConvert::PO_LDR, PVRTexConvert::AO_GRADIENT, PVRTexConvert::CO_COLOR, PVRTexConvert::CO_COMPRESS   , 1); // OGL_PVRTC2
	//pixelType = PVRTexConvert::getPixelType(PVRTexConvert::PO_LDR, PVRTexConvert::AO_GRADIENT, PVRTexConvert::CO_COLOR, PVRTexConvert::CO_COMPRESS   , 2); // OGL_PVRTC4
	//pixelType = PVRTexConvert::getPixelType(PVRTexConvert::PO_LDR, PVRTexConvert::AO_GRADIENT, PVRTexConvert::CO_COLOR, PVRTexConvert::CO_NO_COMPRESS, 0); // OGL_RGBA_4444
	//pixelType = PVRTexConvert::getPixelType(PVRTexConvert::PO_LDR, PVRTexConvert::AO_GRADIENT, PVRTexConvert::CO_COLOR, PVRTexConvert::CO_NO_COMPRESS, 1); // OGL_RGBA_5551
	//pixelType = PVRTexConvert::getPixelType(PVRTexConvert::PO_LDR, PVRTexConvert::AO_GRADIENT, PVRTexConvert::CO_COLOR, PVRTexConvert::CO_NO_COMPRESS, 2); // OGL_RGBA_8888
	//pixelType = PVRTexConvert::getPixelType(PVRTexConvert::PO_LDR, PVRTexConvert::AO_GRADIENT, PVRTexConvert::CO_GRAYSCALE , PVRTexConvert::CO_NO_COMPRESS, 0); // OGL_AI_88
	//pixelType = PVRTexConvert::getPixelType(PVRTexConvert::PO_LDR, PVRTexConvert::AO_GRADIENT, PVRTexConvert::CO_NONE , PVRTexConvert::CO_NO_COMPRESS, 0); // OGL_A_8
	//pixelType = PVRTexConvert::getPixelType(PVRTexConvert::PO_LDR, PVRTexConvert::AO_NONE	 , PVRTexConvert::CO_COLOR, PVRTexConvert::CO_NO_COMPRESS, 0	); // OGL_RGB_565
	//pixelType = PVRTexConvert::getPixelType(PVRTexConvert::PO_LDR, PVRTexConvert::AO_NONE	 , PVRTexConvert::CO_COLOR     , PVRTexConvert::CO_NO_COMPRESS, 1	); // OGL_RGB_888
	//pixelType = PVRTexConvert::getPixelType(PVRTexConvert::PO_LDR, PVRTexConvert::AO_NONE	 , PVRTexConvert::CO_GRAYSCALE , PVRTexConvert::CO_NO_COMPRESS, 0	); // OGL_I_8
	//pixelType = PVRTexConvert::getPixelType(PVRTexConvert::PO_LDR, PVRTexConvert::AO_NONE	 , PVRTexConvert::CO_NONE      , PVRTexConvert::CO_NO_COMPRESS, 0	); // OGL_A_8
	pixelType = PVRTexConvert::getPixelType(precision, alpha, chrome, compress, quality);

	if( strcasecmp(srcFilename_, "../rawAssets/OGL_PVRTC2.png")==0 )
		pixelType = OGL_PVRTC2;
	else if( strcasecmp(srcFilename_, "../rawAssets/OGL_PVRTC4.png")==0 )
		pixelType = OGL_PVRTC4;
	else if( strcasecmp(srcFilename_, "../rawAssets/OGL_RGBA_4444.png")==0 )
		pixelType = OGL_RGBA_4444;
	else if( strcasecmp(srcFilename_, "../rawAssets/OGL_RGBA_5551.png")==0 )
		pixelType = OGL_RGBA_5551;
	else if( strcasecmp(srcFilename_, "../rawAssets/OGL_RGBA_8888.png")==0 )
		pixelType = OGL_RGBA_8888;
	else if( strcasecmp(srcFilename_, "../rawAssets/OGL_RGB_565.png")==0 )
		pixelType = OGL_RGB_565;
	else if( strcasecmp(srcFilename_, "../rawAssets/OGL_RGB_888.png")==0 )
		pixelType = OGL_RGB_888;
	else if( strcasecmp(srcFilename_, "../rawAssets/OGL_AI_88.png")==0 )
		pixelType = OGL_AI_88;
	else if( strcasecmp(srcFilename_, "../rawAssets/OGL_I_8.png")==0 )
		pixelType = OGL_I_8;
	else if( strcasecmp(srcFilename_, "../rawAssets/OGL_A_8.png")==0 )
		pixelType = OGL_A_8;

	exportTexture(srcFilename_, dstFilename_, pixelType);

	return true;
}

bool TextureCubeFile::ResourceImporter::onDeleteFile(const char *srcFilename_)
{
	return this->defaultDeleteFileFunc(srcFilename_);
}

///////////////////////////////////////////////////////////////////////////////////
bool TextureCubeFile::ResourceImporter::exportTexture(const char *srcFilename_, const char *dstFilename_, unsigned int pixelType)
{
	Vector<unsigned char> textureBuf;
	int width, height, numMipMaps;
	
	if( !makeRawTexture(textureBuf, 
					    width, height, numMipMaps,
					    srcFilename_, pixelType) )
		return false;

	CPVRTexture *texture = (CPVRTexture *)PVRTexConvert::makePVRTexture(&textureBuf[0], 
																		width, height, 
																		numMipMaps, 6,
																		true, false, 
																		pixelType);
	if(!texture)
		return false;

	TextureCubeFile::Data data;
	data.version	= 0x01;
	data.platform	= Platform::PC;

	bool rval = writeTexture(dstFilename_, data, texture);
	delete texture;

	//defaultDeleteFileFunc(dstFilename_);
	
	return rval;
}

// surface description flags
const unsigned long DDSF_CAPS           = 0x00000001l;
const unsigned long DDSF_HEIGHT         = 0x00000002l;
const unsigned long DDSF_WIDTH          = 0x00000004l;
const unsigned long DDSF_PITCH          = 0x00000008l;
const unsigned long DDSF_PIXELFORMAT    = 0x00001000l;
const unsigned long DDSF_MIPMAPCOUNT    = 0x00020000l;
const unsigned long DDSF_LINEARSIZE     = 0x00080000l;
const unsigned long DDSF_DEPTH          = 0x00800000l;

// pixel format flags
const unsigned long DDSF_ALPHAPIXELS    = 0x00000001l;
const unsigned long DDSF_FOURCC         = 0x00000004l;
const unsigned long DDSF_RGB            = 0x00000040l;
const unsigned long DDSF_RGBA           = 0x00000041l;

// dwCaps1 flags
const unsigned long DDSF_COMPLEX         = 0x00000008l;
const unsigned long DDSF_TEXTURE         = 0x00001000l;
const unsigned long DDSF_MIPMAP          = 0x00400000l;

// dwCaps2 flags
const unsigned long DDSF_CUBEMAP         = 0x00000200l;
const unsigned long DDSF_CUBEMAP_POSITIVEX  = 0x00000400l;
const unsigned long DDSF_CUBEMAP_NEGATIVEX  = 0x00000800l;
const unsigned long DDSF_CUBEMAP_POSITIVEY  = 0x00001000l;
const unsigned long DDSF_CUBEMAP_NEGATIVEY  = 0x00002000l;
const unsigned long DDSF_CUBEMAP_POSITIVEZ  = 0x00004000l;
const unsigned long DDSF_CUBEMAP_NEGATIVEZ  = 0x00008000l;
const unsigned long DDSF_CUBEMAP_ALL_FACES  = 0x0000FC00l;
const unsigned long DDSF_VOLUME          = 0x00200000l;

// compressed texture types
const unsigned long FOURCC_DXT1 = 0x31545844l; //(MAKEFOURCC('D','X','T','1'))
const unsigned long FOURCC_DXT3 = 0x33545844l; //(MAKEFOURCC('D','X','T','3'))
const unsigned long FOURCC_DXT5 = 0x35545844l; //(MAKEFOURCC('D','X','T','5'))

struct DXTColBlock
{
    unsigned short col0;
    unsigned short col1;

    unsigned char row[4];
};

struct DXT3AlphaBlock
{
    unsigned short row[4];
};

struct DXT5AlphaBlock
{
    unsigned char alpha0;
    unsigned char alpha1;
    
    unsigned char row[6];
};

struct DDS_PIXELFORMAT
{
    unsigned long dwSize;
    unsigned long dwFlags;
    unsigned long dwFourCC;
    unsigned long dwRGBBitCount;
    unsigned long dwRBitMask;
    unsigned long dwGBitMask;
    unsigned long dwBBitMask;
    unsigned long dwABitMask;
};

struct DDS_HEADER
{
    unsigned long dwSize;
    unsigned long dwFlags;
    unsigned long dwHeight;
    unsigned long dwWidth;
    unsigned long dwPitchOrLinearSize;
    unsigned long dwDepth;
    unsigned long dwMipMapCount;
    unsigned long dwReserved1[11];
    DDS_PIXELFORMAT ddspf;
    unsigned long dwCaps1;
    unsigned long dwCaps2;
    unsigned long dwReserved2[3];
};


typedef enum TextureType
{
    TextureNone,
    TextureFlat,    // 1D, 2D, and rectangle textures
    Texture3D,
    TextureCubemap
};

///////////////////////////////////////////////////////////////////////////////////////////////
// clamps input size to [1-size]
unsigned int clampSize(unsigned int size)
{
    if (size <= 0)
        size = 1;

    return size;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// CDDSImage private functions
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////
// calculates size of uncompressed RGB texture in bytes
unsigned int sizeRGB(unsigned int width, unsigned int height, int components)
{
    return width*height*components;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Swap the bytes in a 32 bit value
void swapEndian(void *val)
{
#ifdef MACOS
    unsigned int *ival = (unsigned int *)val;

    *ival = ((*ival >> 24) & 0x000000ff) |
            ((*ival >>  8) & 0x0000ff00) |
            ((*ival <<  8) & 0x00ff0000) |
            ((*ival << 24) & 0xff000000);
#endif
}

bool TextureCubeFile::ResourceImporter::makeRawTexture(Vector<unsigned char> &textureBuf, 
													   int &topLevelMipmapWidth, int &topLevelMipmapHeight, int &numberMipMapsLevel,
													   const char *srcFilename_, unsigned int pixelType)
{
	TextureType type;
	int components;

	FileInputStream fis(srcFilename_);
	if(!fis.opened())
		return false;

    // read in file marker, make sure its a DDS file
    char filecode[4];
	fis.readX(&filecode[0], 4);
	if(System::strncmp(filecode, "DDS ", 4) != 0)
    {
        return false;
    }

    // read in DDS header
    DDS_HEADER ddsh;
	fis.readX(&ddsh, sizeof(DDS_HEADER));

    swapEndian(&ddsh.dwSize);
    swapEndian(&ddsh.dwFlags);
    swapEndian(&ddsh.dwHeight);
    swapEndian(&ddsh.dwWidth);
    swapEndian(&ddsh.dwPitchOrLinearSize);
    swapEndian(&ddsh.dwMipMapCount);
    swapEndian(&ddsh.ddspf.dwSize);
    swapEndian(&ddsh.ddspf.dwFlags);
    swapEndian(&ddsh.ddspf.dwFourCC);
    swapEndian(&ddsh.ddspf.dwRGBBitCount);
    swapEndian(&ddsh.dwCaps1);
    swapEndian(&ddsh.dwCaps2);

	type = TextureCubemap;
	// check if image is a cubemap
    if(!(ddsh.dwCaps2 & DDSF_CUBEMAP))
		return false;

    // figure out what the image format is
    if (ddsh.ddspf.dwFlags & DDSF_FOURCC) 
    {
		return false;
    }
    else if (ddsh.ddspf.dwFlags == DDSF_RGBA && ddsh.ddspf.dwRGBBitCount == 32)
    {
        components = 4;
    }
    else if (ddsh.ddspf.dwFlags == DDSF_RGB  && ddsh.ddspf.dwRGBBitCount == 32)
    {
        components = 4;
    }
    else if (ddsh.ddspf.dwFlags == DDSF_RGB  && ddsh.ddspf.dwRGBBitCount == 24)
    {
        return false;
    }
	else if (ddsh.ddspf.dwRGBBitCount == 8)
	{
		return false;
	}
    else 
    {
        return false;
    }
    
    // store primary surface width/height/depth
    unsigned int width, height, depth;
    width	= ddsh.dwWidth;
    height	= ddsh.dwHeight;
    depth	= clampSize(ddsh.dwDepth);   // set to 1 if 0

    unsigned int (*sizefunc)(unsigned int, unsigned int, int);
    sizefunc = &sizeRGB;

	textureBuf.resize(sizefunc(width, height, components) * depth *6);
	int totalDataSize = 0;
    
    // load all surfaces for the image (6 surfaces for cubemaps)
    for (unsigned int n = 0; n < (unsigned int)(type == TextureCubemap ? 6 : 1); n++)
    {
        // calculate surface size
        unsigned int size = sizefunc(width, height, components) * depth;

        // load surface
		fis.readX(&textureBuf[totalDataSize], size);
		totalDataSize += size;
        //if(flipImage) 
			//flip(img);
        
        unsigned int w = clampSize(width  >> 1);
        unsigned int h = clampSize(height >> 1);
        unsigned int d = clampSize(depth  >> 1); 

        // store number of mipmaps
        unsigned int numMipmaps = ddsh.dwMipMapCount;

        // number of mipmaps in file includes main surface so decrease count 
        // by one
        if (numMipmaps != 0)
            numMipmaps--;

        // load all mipmaps for current surface
        for(unsigned int i=0; i<numMipmaps && (w || h); i++)
        {
            // calculate mipmap size
            size = sizefunc(w, h, components)*d;

			fis.skip(size);
            //if(flipImage) 
				//flip(mipmap);

            // shrink to next power of 2
            w = clampSize(w >> 1);
            h = clampSize(h >> 1);
            d = clampSize(d >> 1); 
        }
    }

	if(pixelType==OGL_RGBA_4444)
		PVRTexConvert::convertToRGBA4444(textureBuf);
	else if(pixelType==OGL_RGBA_5551)
		PVRTexConvert::convertToRGBA5551(textureBuf);
	else if(pixelType==OGL_RGB_555)
		PVRTexConvert::convertToRGB555(textureBuf);
	else if(pixelType==OGL_RGB_565)
		PVRTexConvert::convertToRGB565(textureBuf);
	else if(pixelType==OGL_RGB_888)
		PVRTexConvert::convertToRGB888(textureBuf);
	else if(pixelType==OGL_AI_88)
		PVRTexConvert::convertToAI88(textureBuf);
	else if(pixelType==OGL_I_8)
		PVRTexConvert::convertToI8(textureBuf);
	else if(pixelType==OGL_A_8)
		PVRTexConvert::convertToA8(textureBuf);

	topLevelMipmapWidth		= width;
	topLevelMipmapHeight	= height;
	numberMipMapsLevel		= 0;

	return true;
}

bool TextureCubeFile::ResourceImporter::writeTexture(const char *dstFilename_, TextureCubeFile::Data &data_, void *texture_)
{
	CPVRTexture *texture = (CPVRTexture *)texture_;

	CPVRTextureHeader	&texHeader	= texture->getHeader();
	CPVRTextureData		&texData	= texture->getData();
	int headerSize	= CPVRTextureHeader::getFileHeaderSize(CPVRTextureHeader::u32CURRENT_VERSION);
	int dataSize	= texData.getDataSize();
	assert(headerSize<=1024);
	unsigned char buf[1024];

#ifdef GZ_RESOURCE
	GZFileOutputStream os(dstFilename_);
#else
	FileOutputStream os(dstFilename_);
#endif
	if(!os.opened())
		return false;

	os << data_;

	/////////////////////////////////////////////////////
	texHeader.writeToPointer(buf);
	os.writeX(buf, headerSize);
	os.writeX(texData.getData(), dataSize);

	/////////////////////////////////////////////////////
	int length = os.tell();
	if(length%2048!=0)
		os.skip(2048-length%2048);

	return true;
}

#endif

////////////////////////////////////////////////////////////////
TextureCubeFile::TextureCubeFile() 
: TextureCubeBase()
, resource(0)
{
}

TextureCubeFile::~TextureCubeFile()
{
	destruct();
}
		
bool TextureCubeFile::construct(const char *path_)
{
	assert(resource==0);

	resource = TextureCubeFile::Resource::get(path_);
	if(!resource)
		return false;

	resource->addReference();
	return true;
}

void TextureCubeFile::destruct()
{
	if(resource)
	{
		resource->release();
		resource = 0;
	}
}

void *TextureCubeFile::getHandle() const
{
	assert(resource);
	
	return resource->getHandle();
}

int TextureCubeFile::getWidth() const
{
	assert(resource);
	
	return resource->getWidth();
}

int TextureCubeFile::getHeight() const
{
	assert(resource);
	
	return resource->getHeight();
}

int TextureCubeFile::getLevelCount() const
{
	assert(resource);
	
	return resource->getLevelCount();
}

bool TextureCubeFile::isRenderable() const
{
	assert(resource);
	
	return resource->isRenderable();
}

bool TextureCubeFile::isPowerOfTwo() const
{
	assert(resource);
	
	return resource->isPowerOfTwo();
}