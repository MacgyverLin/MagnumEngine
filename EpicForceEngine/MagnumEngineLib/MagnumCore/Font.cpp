///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "Font.h"
#include "EString.h"
#include "InputStream.h"
#include "Video.h"
#include "GXTexture2D.h"
#ifdef ENABLE_RESOURCE_IMPORT
#include "unzip.h"
#endif
using namespace Magnum;

////////////////////////////////////////////////////////////////
Font::Quad::Quad()
{
	u0		= 0;
	v0		= 0;

	u1		= 0.001;
	v1		= 0.001;

	width	= 1;
	height	= 1;

	pre		= 0;
	post	= 0;
}

Font::Quad::~Quad()
{
}

void Font::Quad::read(InputStream &is)
{
	is >> u0 >> v0;
	is >> u1 >> v1;
	is >> width;
	is >> height;

	is >> pre >> post;
}

void Font::Quad::write(OutputStream &os) const
{
	os << u0 << v0;
	os << u1 << v1;
	os << width;
	os << height;

	os << pre << post;
}

////////////////////////////////////////////////////////////////
Font::Data::Data()
: version(0)
, platform(Platform::PC)
, textureHandle(0)
{
}

Font::Data::~Data()
{
}

int Font::Data::getNumQuads() const
{
	return quads.length();
}

const Font::Quad &Font::Data::getQuad(int i) const
{
	return quads[i];
}

void Font::Data::read(InputStream &is)
{
	is >> version;
	is >> platform;
	is >> maxHeight;
	is >> quads;
}

void Font::Data::write(OutputStream &os) const
{
	os << version;
	os << platform;
	os << maxHeight;
	os << quads;
}

////////////////////////////////////////////////////////////////
Font::Resource::Resource(const char *path_)
: ResourceAccess(path_)
{
}

Font::Resource::~Resource()
{
	onDestroy();
}

void *Font::Resource::getHandle() const
{
	return data.textureHandle;
}

int Font::Resource::getFontMaxHeight() const
{
	return data.maxHeight;
}

int Font::Resource::getFontWidth(char c) const
{
	return data.quads[c].width;
}

int Font::Resource::getFontHeight(char c) const
{
	return data.quads[c].height;
}

int Font::Resource::getWidth() const
{
	assert(data.textureHandle);

	GXTexture2D *texture = (GXTexture2D *)data.textureHandle;
	
	return texture->getWidth();
}

int Font::Resource:: getHeight() const
{
	assert(data.textureHandle);

	GXTexture2D *texture = (GXTexture2D *)data.textureHandle;
	
	return texture->getHeight();
}

int Font::Resource::getLevelCount() const
{
	assert(data.textureHandle);

	GXTexture2D *texture = (GXTexture2D *)data.textureHandle;
	
	return texture->getLevelCount();
}

bool Font::Resource::isRenderable() const
{
	assert(data.textureHandle);

	GXTexture2D *texture = (GXTexture2D *)data.textureHandle;
	
	return texture->isRenderable();
}

bool Font::Resource::isPowerOfTwo() const
{
	assert(data.textureHandle);

	GXTexture2D *texture = (GXTexture2D *)data.textureHandle;
	
	return texture->isPowerOfTwo();
}

unsigned char *Font::Resource::onCreate(int length_)
{
	buffer.resize(length_);

	return &buffer[0];
}

void Font::Resource::onLoaded()
{
	MemInputStream is(&buffer[0], buffer.length());

	is >> data;
	
	int position = is.tell();
	GXTexture2D *texture = new GXTexture2D((const char *)&buffer[position], buffer.length()-position);
	data.textureHandle = (void *)texture;
	assert(data.textureHandle);

	buffer.destroy();
}

void Font::Resource::onDestroy()
{
	if(data.textureHandle)
	{
		GXTexture *texture = (GXTexture *)data.textureHandle;

		delete texture;
		data.textureHandle = 0;
	}

	buffer.destroy();
}

int Font::Resource::getNumQuads() const
{
	return data.getNumQuads();
}

const Font::Quad &Font::Resource::getQuad(int i) const
{
	return data.getQuad(i);
}


#ifdef ENABLE_RESOURCE_IMPORT

#include "gldef.h"

#include <IL\il.h>
#include <IL\ilu.h>

#include "PVRTexConvert.h"
#include "PVRTexLib.h"
using namespace pvrtexlib;

Font::ResourceImporter::ResourceImporter(const char *path_)
: ResourceImport(path_)
, precision(PVRTexConvert::PO_LDR)
, alpha(PVRTexConvert::AO_GRADIENT)
, chrome(PVRTexConvert::CO_COLOR)
, compress(PVRTexConvert::CO_NO_COMPRESS)
, quality(2)
{
}

Font::ResourceImporter::~ResourceImporter()
{
}

bool Font::ResourceImporter::initiate()
{
	ilInit();

	return true;
}

void Font::ResourceImporter::terminate()
{
	ilShutDown();
}

bool Font::ResourceImporter::onExportFile(const char *srcFilename_, const char *dstFilename_)
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

	return exportFont(srcFilename_, dstFilename_, pixelType);
}

bool Font::ResourceImporter::onDeleteFile(const char *srcFilename_)
{
	return this->defaultDeleteFileFunc(srcFilename_);
}

///////////////////////////////////////////////////////////////////////////////////
char *Font::ResourceImporter::_get_line(char *file, char *line)
{
	int i=0;

	if(!file[i]) return 0;

	while(file[i] && file[i]!='\n' && file[i]!='\r')
	{
		line[i]=file[i];
		i++;
	}
	line[i]=0;

	while(file[i] && (file[i]=='\n' || file[i]=='\r')) i++;

	return file + i;
}

const char FNTHEADERTAG[] = "[HGEFONT]";
const char FNTBITMAPTAG[] = "Bitmap";
const char FNTCHARTAG[]   = "Char";

bool Font::ResourceImporter::makeFontInfo(const char *srcFilename_, Vector<Font::Quad> &quads, float &maxHeight)
{
	quads.resize(256);

    unzFile zipfile = unzOpen(srcFilename_);
	int numQuads = 0;
	int	i, x, y, w, h, a, c;
	char chr;

    if(zipfile)
	{
		do
		{
		   // Get info about current file.
			unz_file_info file_info;
			char filename[4096];
			if(unzGetCurrentFileInfo(zipfile, &file_info, filename, 4096, 0, 0, 0, 0) != UNZ_OK)
			{
				debug("could not read file info");
				unzClose( zipfile );
				return false;
			}

			// Check if this entry is a directory or file.
			const size_t filename_length = strlen( filename );
			if(stricmp(&filename[filename_length-4], ".fnt")==0)
			{
				if(unzOpenCurrentFile(zipfile)!=UNZ_OK)
				{
					unzClose(zipfile);
					return false;
				}

				Vector<char> buffer;
				buffer.resize(file_info.uncompressed_size+1);
				unzReadCurrentFile(zipfile,	&buffer[0], file_info.uncompressed_size);
				unzCloseCurrentFile(zipfile);
				buffer[file_info.uncompressed_size]=0;

				char *bufferPtr = &buffer[0];
				char linebuf[256];
				char buf[512];
				char *pbuf;

				bufferPtr = _get_line(bufferPtr, linebuf);
				if(strcmp(linebuf, FNTHEADERTAG))
				{
					debug("Font %s has incorrect format.", srcFilename_);
					return false;
				}

				while((bufferPtr = _get_line(bufferPtr, linebuf))!=NULL)
				{
					if(!strncmp(linebuf, FNTBITMAPTAG, sizeof(FNTBITMAPTAG)-1 ))
					{
						strcpy(buf, filename);
						pbuf=strrchr(buf, '\\');
						if(!pbuf) 
							pbuf=strrchr(buf, '/');
						if(!pbuf) 
							pbuf=buf;
						else 
							pbuf++;
						if(!sscanf(linebuf, "Bitmap = %s", pbuf)) 
							continue;

						//hTexture=hge->Texture_Load(buf, 0, bMipmap);
						//hTexture = renderer->LoadTexture(buf, directory);
						//if(!hTexture)
						if(strlen(buf)==0)
						{
							return false;
						}
					}
					else if(!strncmp(linebuf, FNTCHARTAG, sizeof(FNTCHARTAG)-1 ))
					{
						pbuf=strchr(linebuf,'=');
						if(!pbuf) 
							continue;
						pbuf++;
						while(*pbuf==' ') 
							pbuf++;
						if(*pbuf=='\"')
						{
							pbuf++;
							i=(unsigned char)*pbuf++;
							pbuf++; // skip "
						}
						else
						{
							i=0;
							while((*pbuf>='0' && *pbuf<='9') || (*pbuf>='A' && *pbuf<='F') || (*pbuf>='a' && *pbuf<='f'))
							{
								chr=*pbuf;
								if(chr >= 'a') 
									chr-='a'-':';
								if(chr >= 'A') 
									chr-='A'-':';
								chr-='0';
								if(chr>0xF) chr=0xF;
								i=(i << 4) | chr;
								pbuf++;
							}
							if(i<0 || i>255) continue;
						}
						sscanf(pbuf, " , %d , %d , %d , %d , %d , %d", &x, &y, &w, &h, &a, &c);

						if(i==32)
						{
							i = 32;
						}

						Font::Quad &quad	= quads[i];
						quad.u0				= x;
						quad.v0				= y;
						quad.u1				= x + w;
						quad.v1				= y + h;
						quad.width			= w;
						quad.height			= h;
						quad.pre			= a;
						quad.post			= c;

						if(maxHeight<quad.height)
							maxHeight = quad.height;
					}
					else
					{
						break;
					}
				}
			}
		}while( unzGoToNextFile(zipfile)!=UNZ_END_OF_LIST_OF_FILE );

		unzClose(zipfile);

		return true;
	}
	else
	{
		return false;
	}
}

bool Font::ResourceImporter::exportFont(const char *srcFilename_, const char *dstFilename_, unsigned int pixelType)
{
	Vector<unsigned char> textureBuf;
	Vector<Font::Quad> quads;
	int texWidth, texHeight, numMipMaps;
	float fontHeight;
	if( !makeFontInfo(srcFilename_, quads, fontHeight) )
		return false;
	
	if( !makeFontTexture(textureBuf, 
						 texWidth, texHeight, numMipMaps,
					     srcFilename_, pixelType) )
		return false;

	for(int i=0; i<quads.length(); i++)
	{
		quads[i].u0		/= texWidth;
		quads[i].v0		/= texHeight;
		quads[i].u1		/= texWidth;
		quads[i].v1		/= texHeight;
		quads[i].width;
		quads[i].height;
	}

	CPVRTexture *texture = (CPVRTexture *)PVRTexConvert::makePVRTexture(&textureBuf[0], 
																		texWidth, texHeight, 
																		numMipMaps, 1,
																		false, false, 
																		pixelType);
	if(!texture)
		return false;
	//texture->writeToFile("font.pvr");

	bool rval = writeFont(dstFilename_, quads, texture, fontHeight);
	delete texture;

	//defaultDeleteFileFunc(dstFilename_);
		
	return rval;
}

bool Font::ResourceImporter::makeFontTexture(Vector<unsigned char> &textureBuf, 
											 int &topLevelMipmapWidth, int &topLevelMipmapHeight, int &numberMipMapsLevel,
											 const char *srcFilename_, unsigned int pixelType)
{
    unzFile zipfile = unzOpen(srcFilename_);
	int numQuads = 0;
    if(zipfile)
	{
		do
		{
		   // Get info about current file.
			unz_file_info file_info;
			char filename[4096];
			if(unzGetCurrentFileInfo(zipfile, &file_info, filename, 4096, 0, 0, 0, 0) != UNZ_OK)
			{
				debug("could not read file info");
				unzClose( zipfile );
				return false;
			}

			// Check if this entry is a directory or file.
			const size_t filename_length = strlen( filename );
			if(stricmp(&filename[filename_length-4], ".png")==0)
			{
				if(unzOpenCurrentFile(zipfile)!=UNZ_OK)
				{
					unzClose(zipfile);
					return false;
				}

				Vector<char> buffer;
				buffer.resize(file_info.uncompressed_size);
				unzReadCurrentFile(zipfile,	&buffer[0], file_info.uncompressed_size);
				unzCloseCurrentFile(zipfile);
				
				unsigned int imageName;
				ilGenImages(1, &imageName);
				ilBindImage(imageName);
				iluImageParameter(ILU_FILTER, ILU_BILINEAR);
								
				if(!ilLoadL(IL_PNG, &buffer[0], buffer.length()))
				{
					unzClose(zipfile);
					return false;
				}

				ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
				//iluFlipImage();
				
				int width	= ilGetInteger(IL_IMAGE_WIDTH);
				int height	= ilGetInteger(IL_IMAGE_HEIGHT); 
				int depth	= ilGetInteger(IL_IMAGE_DEPTH); 
				int bpp		= ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
				int format	= ilGetInteger(IL_IMAGE_FORMAT);
				int dataSize= ilGetInteger(IL_IMAGE_SIZE_OF_DATA);
				textureBuf.resize(dataSize);

				ilCopyPixels(0, 0, 0,
							 width, height, 1, 
							 IL_RGBA, IL_UNSIGNED_BYTE,
							 &textureBuf[0]);

				ilDeleteImages(1, &imageName);

				topLevelMipmapWidth		= width;
				topLevelMipmapHeight	= height;
				numberMipMapsLevel		= 0;

				break;
			};
		}while( unzGoToNextFile(zipfile)!=UNZ_END_OF_LIST_OF_FILE );

		unzClose(zipfile);

		return true;
	}
	else
	{
		return false;
	}
}

bool Font::ResourceImporter::writeFont(const char *dstFilename_, Vector<Font::Quad> &quads, void *texture_, float fontHeight)
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

	int version							= 0;
	int platform						= 1;
	os << version;
	os << platform;

	/////////////////////////////////////////////////////
	os << fontHeight;
	os << quads;

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
Font::Font() 
: Texture2DBase()
, resource(0)
{
}

Font::~Font()
{
	destruct();
}
		
bool Font::construct(const char *path_)
{
	assert(resource==0);

	resource = Font::Resource::get(path_);
	if(!resource)
		return false;

	resource->addReference();
	return true;
}

void Font::destruct()
{
	if(resource)
	{
		resource->release();
		resource = 0;
	}
}

void *Font::getHandle() const
{
	assert(resource);
	
	return resource->getHandle();
}

int Font::getFontMaxHeight() const
{
	assert(resource);
	
	return resource->getFontMaxHeight();
}

int Font::getFontWidth(char c) const
{
	assert(resource);
	
	return resource->getFontWidth(c);
}

int Font::getFontHeight(char c) const
{
	assert(resource);
	
	return resource->getFontHeight(c);
}

int Font::getWidth() const
{
	assert(resource);
	
	return resource->getWidth();
}

int Font::getHeight() const
{
	assert(resource);
	
	return resource->getHeight();
}

int Font::getLevelCount() const
{
	assert(resource);
	
	return resource->getLevelCount();
}

bool Font::isRenderable() const
{
	assert(resource);
	
	return resource->isRenderable();
}

bool Font::isPowerOfTwo() const
{
	assert(resource);
	
	return resource->isPowerOfTwo();
}

int Font::getNumQuads() const
{
	assert(resource);
	
	return resource->getNumQuads();
}

const Font::Quad &Font::getQuad(int i) const
{
	assert(resource);
	
	return resource->getQuad(i);
}