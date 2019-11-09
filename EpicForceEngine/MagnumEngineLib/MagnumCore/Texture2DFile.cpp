///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "Texture2DFile.h"
#include "EString.h"
#include "InputStream.h"
#include "Video.h"
#include "GXTexture2D.h"
using namespace Magnum;

Texture2DFile::Data::Data()
: version(0)
, platform(Platform::PC)
, textureHandle(0)
{
}

Texture2DFile::Data::~Data()
{
}

void Texture2DFile::Data::read(InputStream &is)
{
	is >> version;
	is >> platform;
}

void Texture2DFile::Data::write(OutputStream &os) const
{
	os << version;
	os << platform;
}

////////////////////////////////////////////////////////////////
Texture2DFile::Resource::Resource(const char *path_)
: ResourceAccess(path_)
{
}	

Texture2DFile::Resource::~Resource()
{
	onDestroy();
}

unsigned char *Texture2DFile::Resource::onCreate(int length_)
{
	buffer.resize(length_);

	return &buffer[0];
}

void Texture2DFile::Resource::onLoaded()
{
	MemInputStream is(&buffer[0], buffer.length());

	is >> data;
	
	int position = is.tell();
	GXTexture2D *texture = new GXTexture2D((const char *)&buffer[position], buffer.length()-position);
	data.textureHandle = (void *)texture;
	assert(data.textureHandle);

	buffer.destroy();
}

void Texture2DFile::Resource::onDestroy()
{
	if(data.textureHandle)
	{
		GXTexture *texture = (GXTexture *)data.textureHandle;

		delete texture;
		data.textureHandle = 0;
	}

	buffer.destroy();
}

void *Texture2DFile::Resource::getHandle() const
{
	return data.textureHandle;
}

int Texture2DFile::Resource::getWidth() const
{
	assert(data.textureHandle);
	GXTexture *texture = (GXTexture *)data.textureHandle;

	return texture->getWidth();
}

int Texture2DFile::Resource::getHeight() const
{
	assert(data.textureHandle);
	GXTexture *texture = (GXTexture *)data.textureHandle;

	return texture->getHeight();
}

int Texture2DFile::Resource::getLevelCount() const
{
	assert(data.textureHandle);
	GXTexture *texture = (GXTexture *)data.textureHandle;

	return texture->getLevelCount();
}

bool Texture2DFile::Resource::isRenderable() const
{
	assert(data.textureHandle);
	GXTexture *texture = (GXTexture *)data.textureHandle;

	return texture->isRenderable();
}

bool Texture2DFile::Resource::isPowerOfTwo() const
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

Texture2DFile::ResourceImporter::ResourceImporter(const char *path_)
: ResourceImport(path_)
, precision(PVRTexConvert::PO_LDR)
, alpha(PVRTexConvert::AO_GRADIENT)
, chrome(PVRTexConvert::CO_COLOR)
, compress(PVRTexConvert::CO_NO_COMPRESS)
, quality(2)
{
}

Texture2DFile::ResourceImporter::~ResourceImporter()
{
}

bool Texture2DFile::ResourceImporter::initiate()
{
	ilInit();

	return true;
}

void Texture2DFile::ResourceImporter::terminate()
{
	ilShutDown();
}

bool Texture2DFile::ResourceImporter::onExportFile(const char *srcFilename_, const char *dstFilename_)
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

bool Texture2DFile::ResourceImporter::onDeleteFile(const char *srcFilename_)
{
	return this->defaultDeleteFileFunc(srcFilename_);
}

///////////////////////////////////////////////////////////////////////////////////
bool Texture2DFile::ResourceImporter::exportTexture(const char *srcFilename_, const char *dstFilename_, unsigned int pixelType)
{
	Vector<unsigned char> textureBuf;
	int width, height, numMipMaps;
	
	if( !makeRawTexture(textureBuf, 
					    width, height, numMipMaps,
					    srcFilename_, pixelType) )
		return false;

	CPVRTexture *texture = (CPVRTexture *)PVRTexConvert::makePVRTexture(&textureBuf[0], 
																		width, height, 
																		numMipMaps, 1,
																		false, false, 
																		pixelType);
	if(!texture)
		return false;

	Texture2DFile::Data data;
	data.version	= 0x01;
	data.platform	= Platform::PC;

	bool rval = writeTexture(dstFilename_, data, texture);
	delete texture;

	//defaultDeleteFileFunc(dstFilename_);
	
	return rval;
}

bool Texture2DFile::ResourceImporter::makeRawTexture(Vector<unsigned char> &textureBuf, 
													 int &topLevelMipmapWidth, int &topLevelMipmapHeight, int &numberMipMapsLevel,
													 const char *srcFilename_, unsigned int pixelType)
{
	/*
	static bool initied = false;
	if(!initied)
	{
		ilInit();
		initied = true;
	}
	*/

	unsigned int ImageName;
	ilGenImages(1, &ImageName);
	ilBindImage(ImageName);
	iluImageParameter(ILU_FILTER, ILU_BILINEAR);

	if( ilLoadImage(srcFilename_) == IL_FALSE )
		return false;

	//unsigned int convertPixelFormat = PVRTexConvert::getConvertFormat(pixelType);
	//unsigned int convertPixelType   = PVRTexConvert::getConvertPixelType(pixelType);
	//if( ilConvertImage(convertPixelFormat, convertPixelType) == IL_FALSE )
		//return false;
	if( ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE) == IL_FALSE )
		return false;

	if( iluFlipImage() == IL_FALSE )
		return false;

	int firstLayerWidth, firstLayerHeight, firstLayerDepth, firstLayerBpp, firstLayerFormat, firstLayerDataSize;
	firstLayerWidth		= ilGetInteger(IL_IMAGE_WIDTH);
	firstLayerHeight	= ilGetInteger(IL_IMAGE_HEIGHT); 
	firstLayerDepth		= ilGetInteger(IL_IMAGE_DEPTH); 
	firstLayerBpp		= ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
	firstLayerFormat	= ilGetInteger(IL_IMAGE_FORMAT);
	firstLayerDataSize	= ilGetInteger(IL_IMAGE_SIZE_OF_DATA);

	textureBuf.clear();
	textureBuf.resize(firstLayerDataSize);
	
	int numMipmaps		= 0;
	int totalDataSize	= 0;
	int width, height, depth, bpp, format, datasize;

	width  = firstLayerWidth;
	height = firstLayerHeight;

	width	= ilGetInteger(IL_IMAGE_WIDTH);
	height	= ilGetInteger(IL_IMAGE_HEIGHT); 
	depth	= ilGetInteger(IL_IMAGE_DEPTH); 
	bpp		= ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
	format	= ilGetInteger(IL_IMAGE_FORMAT);
	datasize= ilGetInteger(IL_IMAGE_SIZE_OF_DATA);
	assert(width*height*bpp==datasize);

	ilCopyPixels(0, 0, 0,
				 width, height, 1, 
				 IL_RGBA, IL_UNSIGNED_BYTE,
				 &textureBuf[totalDataSize]);

	totalDataSize += datasize;
	
	//pixelType = OGL_PVRTC2;
	//pixelType = OGL_PVRTC4;
	//pixelType = OGL_RGBA_8888;
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

	ilDeleteImages(1, &ImageName);

	topLevelMipmapWidth		= firstLayerWidth;
	topLevelMipmapHeight	= firstLayerHeight;
	numberMipMapsLevel		= 0;

	return true;
}


#if 0
bool Texture2DFile::ResourceImporter::makeRawTexture(Vector<unsigned char> &textureBuf, 
													 int &topLevelMipmapWidth, int &topLevelMipmapHeight, int &numberMipMapsLevel,
													 const char *srcFilename_, unsigned int pixelType)
{
	/*
	static bool initied = false;
	if(!initied)
	{
		ilInit();
		initied = true;
	}
	*/

	unsigned int ImageName;
	ilGenImages(1, &ImageName);
	ilBindImage(ImageName);
	iluImageParameter(ILU_FILTER, ILU_BILINEAR);

	if( ilLoadImage(srcFilename_) == IL_FALSE )
		return false;

	//unsigned int convertPixelFormat = PVRTexConvert::getConvertFormat(pixelType);
	//unsigned int convertPixelType   = PVRTexConvert::getConvertPixelType(pixelType);
	//if( ilConvertImage(convertPixelFormat, convertPixelType) == IL_FALSE )
		//return false;
	if( ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE) == IL_FALSE )
		return false;

	if( iluFlipImage() == IL_FALSE )
		return false;

	int firstLayerWidth, firstLayerHeight, firstLayerDepth, firstLayerBpp, firstLayerFormat, firstLayerDataSize;
	firstLayerWidth		= ilGetInteger(IL_IMAGE_WIDTH);
	firstLayerHeight	= ilGetInteger(IL_IMAGE_HEIGHT); 
	firstLayerDepth		= ilGetInteger(IL_IMAGE_DEPTH); 
	firstLayerBpp		= ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
	firstLayerFormat	= ilGetInteger(IL_IMAGE_FORMAT);
	firstLayerDataSize	= ilGetInteger(IL_IMAGE_SIZE_OF_DATA);

	textureBuf.clear();
	textureBuf.resize(firstLayerDataSize + firstLayerDataSize/2);
	
	int numMipmaps		= 0;
	int totalDataSize	= 0;
	int width, height, depth, bpp, format, datasize;
	do
	{
		int div = pow(2.0f, numMipmaps);
		width  = firstLayerWidth  / div;
		height = firstLayerHeight / div;
		if(div!=1)
		{
			if( iluScale(width, height, 1) == IL_FALSE)
				return false;
		}

		width	= ilGetInteger(IL_IMAGE_WIDTH);
		height	= ilGetInteger(IL_IMAGE_HEIGHT); 
		depth	= ilGetInteger(IL_IMAGE_DEPTH); 
		bpp		= ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
		format	= ilGetInteger(IL_IMAGE_FORMAT);
		datasize= ilGetInteger(IL_IMAGE_SIZE_OF_DATA);
		assert(width*height*bpp==datasize);
		/*
		ilCopyPixels(0, 0, 0,
					 width, height, 1, 
					 convertPixelFormat,
					 convertPixelType,
					 &buf[totalDataSize]);
		*/
		ilCopyPixels(0, 0, 0,
					 width, height, 1, 
					 IL_RGBA, IL_UNSIGNED_BYTE,
					 &textureBuf[totalDataSize]);

		totalDataSize += datasize;
		numMipmaps++;
		assert(totalDataSize<=textureBuf.length());
	}while(width>=32 && height>=32 && numMipmaps<10);

	//pixelType = OGL_PVRTC2;
	//pixelType = OGL_PVRTC4;
	//pixelType = OGL_RGBA_8888;
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

	ilDeleteImages(1, &ImageName);

	topLevelMipmapWidth		= firstLayerWidth;
	topLevelMipmapHeight	= firstLayerHeight;
	numberMipMapsLevel		= numMipmaps-1;

	return true;
}
#endif

bool Texture2DFile::ResourceImporter::writeTexture(const char *dstFilename_, Texture2DFile::Data &data_, void *texture_)
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
Texture2DFile::Texture2DFile() 
: Texture2DBase()
, resource(0)
{
}

Texture2DFile::~Texture2DFile()
{
	destruct();
}
		
bool Texture2DFile::construct(const char *path_)
{
	assert(resource==0);

	resource = Texture2DFile::Resource::get(path_);
	if(!resource)
		return false;

	resource->addReference();
	return true;
}

void Texture2DFile::destruct()
{
	if(resource)
	{
		resource->release();
		resource = 0;
	}
}

void *Texture2DFile::getHandle() const
{
	assert(resource);
	
	return resource->getHandle();
}

int Texture2DFile::getWidth() const
{
	assert(resource);
	
	return resource->getWidth();
}

int Texture2DFile::getHeight() const
{
	assert(resource);
	
	return resource->getHeight();
}

int Texture2DFile::getLevelCount() const
{
	assert(resource);
	
	return resource->getLevelCount();
}

bool Texture2DFile::isRenderable() const
{
	assert(resource);
	
	return resource->isRenderable();
}

bool Texture2DFile::isPowerOfTwo() const
{
	assert(resource);
	
	return resource->isPowerOfTwo();
}