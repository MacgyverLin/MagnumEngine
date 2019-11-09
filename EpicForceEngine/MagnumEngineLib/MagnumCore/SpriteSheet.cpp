///////////////////////////////////////////////////////////////////////////////////
// Copyright(c) 2016, Lin Koon Wing Macgyver, macgyvercct@yahoo.com.hk			 //
//																				 //
// Author : Mac Lin									                             //
// Module : Magnum Engine v1.0.0												 //
// Date   : 14/Jun/2016											                 //
//																				 //
///////////////////////////////////////////////////////////////////////////////////
#include "Stage.h"
#include "SpriteSheet.h"
#include "EString.h"
#include "InputStream.h"
#include "Video.h"
#include "GXTexture2D.h"
#ifdef ENABLE_RESOURCE_IMPORT
#include "unzip.h"
#endif
using namespace Magnum;

#define MAX_TEXTURE_WIDTH  2048
#define QUADGAPSIZE 4

////////////////////////////////////////////////////////////////
SpriteSheet::Quad::Quad()
{
}

SpriteSheet::Quad::~Quad()
{
}

void SpriteSheet::Quad::read(InputStream &is)
{
	is >> u0 >> v0;
	is >> u1 >> v1;
	is >> width;
	is >> height;
}

void SpriteSheet::Quad::write(OutputStream &os) const
{
	os << u0 << v0;
	os << u1 << v1;
	os << width;
	os << height;
}

///////////////////////////////////////////////////////////////
SpriteSheet::Sequence::Sequence()
{
}

SpriteSheet::Sequence::~Sequence()
{
}

const String &SpriteSheet::Sequence::getName() const
{
	return name;
}

int SpriteSheet::Sequence::getNumFrames() const
{
	return endIndex - startIndex + 1;
}

int SpriteSheet::Sequence::getStartIndex() const
{
	return startIndex;
}

int SpriteSheet::Sequence::getEndIndex() const
{
	return endIndex;
}

void SpriteSheet::Sequence::read(InputStream &is)
{
	is >> name;
	is >> startIndex;
	is >> endIndex;
}

void SpriteSheet::Sequence::write(OutputStream &os) const
{
	os << name;
	os << startIndex;
	os << endIndex;
}

////////////////////////////////////////////////////////////////
SpriteSheet::Data::Data()
: version(0)
, platform(Platform::PC)
, textureHandle(0)
{
}

SpriteSheet::Data::~Data()
{
}

int SpriteSheet::Data::getNumQuads() const
{
	return quads.length();
}

const SpriteSheet::Quad &SpriteSheet::Data::getQuad(int i) const
{
	return quads[i];
}

int SpriteSheet::Data::getNumSequences() const
{
	return sequences.length();
}

const SpriteSheet::Sequence &SpriteSheet::Data::getSequence(int i) const
{
	return sequences[i];
}

void SpriteSheet::Data::read(InputStream &is)
{
	is >> version;
	is >> platform;
	is >> sequences;
	is >> quads;
}

void SpriteSheet::Data::write(OutputStream &os) const
{
	os << version;
	os << platform;
	os << sequences;
	os << quads;
}

////////////////////////////////////////////////////////////////
SpriteSheet::Resource::Resource(const char *path_)
: ResourceAccess(path_)
{
}	

SpriteSheet::Resource::~Resource()
{
	onDestroy();
}

void *SpriteSheet::Resource::getHandle() const
{
	return data.textureHandle;
}

int SpriteSheet::Resource::getWidth() const
{
	assert(data.textureHandle);

	GXTexture2D *texture = (GXTexture2D *)data.textureHandle;
	
	return texture->getWidth();
}

int SpriteSheet::Resource:: getHeight() const
{
	assert(data.textureHandle);

	GXTexture2D *texture = (GXTexture2D *)data.textureHandle;
	
	return texture->getHeight();
}

int SpriteSheet::Resource::getLevelCount() const
{
	assert(data.textureHandle);

	GXTexture2D *texture = (GXTexture2D *)data.textureHandle;
	
	return texture->getLevelCount();
}

bool SpriteSheet::Resource::isRenderable() const
{
	assert(data.textureHandle);

	GXTexture2D *texture = (GXTexture2D *)data.textureHandle;
	
	return texture->isRenderable();
}

bool SpriteSheet::Resource::isPowerOfTwo() const
{
	assert(data.textureHandle);

	GXTexture2D *texture = (GXTexture2D *)data.textureHandle;
	
	return texture->isPowerOfTwo();
}

unsigned char *SpriteSheet::Resource::onCreate(int length_)
{
	buffer.resize(length_);

	return &buffer[0];
}

void SpriteSheet::Resource::onLoaded()
{
	MemInputStream is(&buffer[0], buffer.length());

	is >> data;
	
	int position = is.tell();
	GXTexture2D *texture = new GXTexture2D((const char *)&buffer[position], buffer.length()-position);
	data.textureHandle = (void *)texture;
	assert(data.textureHandle);

	buffer.destroy();
}

void SpriteSheet::Resource::onDestroy()
{
	if(data.textureHandle)
	{
		GXTexture *texture = (GXTexture *)data.textureHandle;

		delete texture;
		data.textureHandle = 0;
	}

	buffer.destroy();
}

int SpriteSheet::Resource::getNumQuads() const
{
	return data.getNumQuads();
}

const SpriteSheet::Quad &SpriteSheet::Resource::getQuad(int i) const
{
	return data.getQuad(i);
}

int SpriteSheet::Resource::getNumSequences() const
{
	return data.getNumSequences();
}

const SpriteSheet::Sequence &SpriteSheet::Resource::getSequence(int i) const
{
	return data.getSequence(i);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef ENABLE_RESOURCE_IMPORT

#include "gldef.h"

#include <IL\il.h>
#include <IL\ilu.h>

#include "PVRTexConvert.h"
#include "PVRTexLib.h"
using namespace pvrtexlib;

SpriteSheet::ResourceImporter::ResourceImporter(const char *path_)
: ResourceImport(path_)
, precision(PVRTexConvert::PO_LDR)
, alpha(PVRTexConvert::AO_GRADIENT)
, chrome(PVRTexConvert::CO_COLOR)
, compress(PVRTexConvert::CO_NO_COMPRESS)
, quality(2)
{
}

SpriteSheet::ResourceImporter::~ResourceImporter()
{
}

bool SpriteSheet::ResourceImporter::initiate()
{
	ilInit();

	return true;
}

void SpriteSheet::ResourceImporter::terminate()
{
	ilShutDown();
}

bool SpriteSheet::ResourceImporter::onExportFile(const char *srcFilename_, const char *dstFilename_)
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

	return exportSpriteSheet(srcFilename_, dstFilename_, pixelType);
}

bool SpriteSheet::ResourceImporter::onDeleteFile(const char *srcFilename_)
{
	return this->defaultDeleteFileFunc(srcFilename_);
}

///////////////////////////////////////////////////////////////////////////////////
int SpriteSheet::ResourceImporter::compareString(const void *left, const void *right)
{
	return strcmp( (*((String *)left)), (*((String *)right)) );
}

bool SpriteSheet::ResourceImporter::exportSpriteSheet(const char *srcFilename_, const char *dstFilename_, unsigned int pixelType)
{
	Vector<unsigned char> textureBuf;
	Vector<SpriteSheet::Quad> quads;
	Vector<SpriteSheet::Sequence> sequences;
	int topLevelMipmapWidth;
	int topLevelMipmapHeight;

	if( !makeSpriteTexture(textureBuf, quads, sequences, 
						   topLevelMipmapWidth, topLevelMipmapHeight, 
						   srcFilename_, pixelType) )
		return false;

	CPVRTexture *texture = (CPVRTexture *)PVRTexConvert::makePVRTexture(&textureBuf[0], 
																		topLevelMipmapWidth, topLevelMipmapHeight, 
																		0, 1,
																		false, false,
																		pixelType);
	if(!texture)
		return false;
	//texture->writeToFile("sprite.pvr");

	bool rval = writeSpriteSheet(dstFilename_, quads, sequences, texture);
	delete texture;

	//defaultDeleteFileFunc(dstFilename_);

	return rval;
}

bool SpriteSheet::ResourceImporter::makeSpriteTexture(Vector<unsigned char> &textureBuf, 
														  Vector<SpriteSheet::Quad> &quads, 
														  Vector<SpriteSheet::Sequence> &sequences, 
														  int &topLevelMipmapWidth, int &topLevelMipmapHeight, 
														  const char *srcFilename_, unsigned int pixelType)
{
	Vector<SpriteSheet::ResourceImporter::QuadBuffer> quadBuffers;
	if(!getSequence(srcFilename_, sequences))
		return false;

	for(int i=0; i<sequences.length(); i++)
	{
		if(!getQuadBuffers(srcFilename_, sequences[i], quadBuffers))
			return false;
	}

	//for(int i=0; i<sequences.length(); i++)
		//debug("%s %d %d", sequences[i].name, sequences[i].startIndex, sequences[i].endIndex);
	//for(int i=0; i<quadBuffers.length(); i++)
		//debug("%s", quadBuffers[i].filename);
		
	///////////////////////////////////////////////////////////////////////////////////
	Vector<SpriteSheet::ResourceImporter::QuadBuffer> sortedQuadBufs;
	sortedQuadBufs = quadBuffers;
	sortedQuadBufs.sort(compareQuadBufs);

	///////////////////////////////////////////////////////////////////////////////////
	int xOffset = 0;
	int yOffset = 0;
	int lastHeight = 0;
	for(int i=0; i<sortedQuadBufs.length(); i++)
	{
		int idx = sortedQuadBufs[i].idx;

		if(xOffset+(quadBuffers[idx].width + QUADGAPSIZE) > MAX_TEXTURE_WIDTH)
		{
			xOffset = 0;
			yOffset += (lastHeight + QUADGAPSIZE);
		}

		quadBuffers[idx].u0 += xOffset;
		quadBuffers[idx].v0 += yOffset;
		quadBuffers[idx].u1 += xOffset;
		quadBuffers[idx].v1 += yOffset;

		xOffset += (quadBuffers[idx].width+QUADGAPSIZE);
		lastHeight = quadBuffers[idx].height;
	}

	topLevelMipmapWidth  = MAX_TEXTURE_WIDTH;
	topLevelMipmapHeight = yOffset + (lastHeight + QUADGAPSIZE);
	topLevelMipmapHeight = Math::CeilPower2(topLevelMipmapHeight);

	///////////////////////////////////////////////////////////////////////////////////
	textureBuf.resize(topLevelMipmapWidth*topLevelMipmapHeight*4);
	System::memset(&textureBuf[0], 0, textureBuf.length());	
	for(int i=0; i<sortedQuadBufs.length(); i++)
	{
		int idx = sortedQuadBufs[i].idx;
		
		drawBitmap(textureBuf, quadBuffers[idx],
				   quadBuffers[idx].u0 , quadBuffers[idx].v0, 
				   quadBuffers[idx].width, quadBuffers[idx].height);

		quadBuffers[idx].u0		/= topLevelMipmapWidth;
		quadBuffers[idx].v0		/= topLevelMipmapHeight;
		quadBuffers[idx].u1		/= topLevelMipmapWidth;
		quadBuffers[idx].v1		/= topLevelMipmapHeight;
		quadBuffers[idx].width;
		quadBuffers[idx].height;
	}

	quads.resize(quadBuffers.length());
	for(int i=0; i<quadBuffers.length(); i++)
	{
		quads[i].u0			= quadBuffers[i].u0;
		quads[i].v0			= quadBuffers[i].v1;
		quads[i].u1			= quadBuffers[i].u1;
		quads[i].v1			= quadBuffers[i].v0;
		quads[i].width		= quadBuffers[i].width;
		quads[i].height		= quadBuffers[i].height;
	}

	return true;
}

bool SpriteSheet::ResourceImporter::getSequence(const char *srcFilename_, 
											   Vector<SpriteSheet::Sequence> &sequences)
{
    unzFile zipfile = unzOpen(srcFilename_);
    if(zipfile)
	{
		do
		{
		   // Get info about current file.
			unz_file_info file_info;
			char filename[4096];
			char dirname[4096];
			if(unzGetCurrentFileInfo(zipfile, &file_info, filename, 4096, 0, 0, 0, 0) != UNZ_OK)
			{
				debug("could not read file info");
				unzClose( zipfile );
				return false;
			}

			// Check if this entry is a directory or file.
			const size_t filename_length = strlen( filename );
			if( filename[ filename_length-1 ] == '/' )
			{
				strncpy(dirname, filename, filename_length-1);
				dirname[filename_length-1] = 0;

				SpriteSheet::Sequence &seq = sequences.push();

				seq.name		= dirname;
				seq.startIndex  = -1;
				seq.endIndex	= -1;
			}
			else if( stricmp(&filename[filename_length-4], ".png")==0)
			{
			}
			else
			{
				unzClose(zipfile);
				return false;
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

bool SpriteSheet::ResourceImporter::getQuadBuffers(const char *srcFilename_, 
												   SpriteSheet::Sequence &sequence,
												   Vector<SpriteSheet::ResourceImporter::QuadBuffer> &quadBuffers)
{
    unzFile zipfile = unzOpen(srcFilename_);
    if(zipfile)
	{
		do
		{
		   // Get info about current file.
			unz_file_info file_info;
			char filename[4096];
			char dirname[4096];
			if(unzGetCurrentFileInfo(zipfile, &file_info, filename, 4096, 0, 0, 0, 0) != UNZ_OK)
			{
				debug("could not read file info");
				unzClose( zipfile );
				return false;
			}

			// Check if this entry is a directory or file.
			const size_t filename_length = strlen( filename );
			if ( filename[ filename_length-1 ] == '/' )
			{
				if( sequence.name + "/" == filename)
				{
					sequence.startIndex = quadBuffers.length();
				}
				else
				{
					if(sequence.startIndex>=0)
					{
						sequence.endIndex = quadBuffers.length() - 1;
						break;
					}
				}
			}
			else if( stricmp(&filename[filename_length-4], ".png")==0 )
			{
				if(sequence.startIndex>=0)
				{
					ResourceImporter::QuadBuffer &quadBuf = quadBuffers.push();

					if( unzOpenCurrentFile(zipfile)!=UNZ_OK )
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
					iluFlipImage();
				
					int width	= ilGetInteger(IL_IMAGE_WIDTH);
					int height	= ilGetInteger(IL_IMAGE_HEIGHT); 
					int depth	= ilGetInteger(IL_IMAGE_DEPTH); 
					int bpp		= ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
					int format	= ilGetInteger(IL_IMAGE_FORMAT);
					int dataSize= ilGetInteger(IL_IMAGE_SIZE_OF_DATA);

					quadBuf.filename				= filename;
					quadBuf.imagename				= imageName;
					quadBuf.idx						= quadBuffers.length() - 1;
					quadBuf.u0						= 0;
					quadBuf.v0						= 0;
					quadBuf.u1						= width;
					quadBuf.v1						= height;
					quadBuf.width					= width;
					quadBuf.height					= height;
				}
			}
			else
			{
				unzClose(zipfile);
				return false;
			}
		}while( unzGoToNextFile(zipfile)!=UNZ_END_OF_LIST_OF_FILE );

		if(sequence.endIndex<0)
			sequence.endIndex = quadBuffers.length() - 1;

		unzClose(zipfile);

		return true;
	}
	else
	{
		return false;
	}
}

void SpriteSheet::ResourceImporter::drawBitmap(Vector<unsigned char> &textureBuf, QuadBuffer &quadBuf, int xOffset, int yOffset, int width, int height)
{
	ilBindImage(quadBuf.imagename);

	int width1	  = ilGetInteger(IL_IMAGE_WIDTH);
	int height1	  = ilGetInteger(IL_IMAGE_HEIGHT); 
	int depth1	  = ilGetInteger(IL_IMAGE_DEPTH); 
	int bpp1	  = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
	int format1	  = ilGetInteger(IL_IMAGE_FORMAT);
	int dataSize1 = ilGetInteger(IL_IMAGE_SIZE_OF_DATA);

	Vector<char> buffer;
	buffer.resize(quadBuf.width * quadBuf.height * 4);
	buffer.resize(dataSize1);

	ilCopyPixels(0, 0, 0,
				 width, height, 1, 
				 IL_RGBA, IL_UNSIGNED_BYTE,
				 &buffer[0]);

	ilDeleteImages(1, &quadBuf.imagename);

	for(int y=0; y<height; y++)
	{
		for(int x=0; x<width; x++)
		{
			textureBuf[((y+yOffset)*MAX_TEXTURE_WIDTH+(x+xOffset))*4+0] = buffer[(y*width+x)*4+0];
			textureBuf[((y+yOffset)*MAX_TEXTURE_WIDTH+(x+xOffset))*4+1] = buffer[(y*width+x)*4+1];
			textureBuf[((y+yOffset)*MAX_TEXTURE_WIDTH+(x+xOffset))*4+2] = buffer[(y*width+x)*4+2];
			textureBuf[((y+yOffset)*MAX_TEXTURE_WIDTH+(x+xOffset))*4+3] = buffer[(y*width+x)*4+3];
		}
	}
}


bool SpriteSheet::ResourceImporter::writeSpriteSheet(const char *dstFilename_, 
															 Vector<SpriteSheet::Quad> &quads, 
															 Vector<SpriteSheet::Sequence> &sequences, 
															 void *texture_)
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
	os << sequences;

	/////////////////////////////////////////////////////
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

int SpriteSheet::ResourceImporter::compareQuadBufs(const void *q1, const void *q2)
{
	return ((SpriteSheet::ResourceImporter::QuadBuffer*)q1)->height - ((SpriteSheet::ResourceImporter::QuadBuffer*)q2)->height;
}

#endif

////////////////////////////////////////////////////////////////
SpriteSheet::SpriteSheet() 
: Texture2DBase()
, resource(0)
{
}

SpriteSheet::~SpriteSheet()
{
	destruct();
}
		
bool SpriteSheet::construct(const char *path_)
{
	assert(resource==0);

	resource = SpriteSheet::Resource::get(path_);
	if(!resource)
		return false;

	resource->addReference();
	return true;
}

void SpriteSheet::destruct()
{
	if(resource)
	{
		resource->release();
		resource = 0;
	}
}

void *SpriteSheet::getHandle() const
{
	assert(resource);
	
	return resource->getHandle();
}

int SpriteSheet::getWidth() const
{
	assert(resource);
	
	return resource->getWidth();
}

int SpriteSheet::getHeight() const
{
	assert(resource);
	
	return resource->getHeight();
}

int SpriteSheet::getLevelCount() const
{
	assert(resource);
	
	return resource->getLevelCount();
}

bool SpriteSheet::isRenderable() const
{
	assert(resource);
	
	return resource->isRenderable();
}

bool SpriteSheet::isPowerOfTwo() const
{
	assert(resource);
	
	return resource->isPowerOfTwo();
}

int SpriteSheet::getNumQuads() const
{
	assert(resource);
	
	return resource->getNumQuads();
}

const SpriteSheet::Quad &SpriteSheet::getQuad(int i) const
{
	assert(resource);
	
	return resource->getQuad(i);
}

int SpriteSheet::getNumSequences() const
{
	assert(resource);
	
	return resource->getNumSequences();
}

const SpriteSheet::Sequence &SpriteSheet::getSequence(int i) const
{
	assert(resource);
	
	return resource->getSequence(i);
}

