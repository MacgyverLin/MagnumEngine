#include "ImageFile.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "assert.h"
#include <IL\il.h>
#include <IL\ilu.h>
using namespace EpicForce;

/////////////////////////////////////////////////////////////
ImageFile::ImageFile() 
: imageName(0)
, width(0)
, height(0)
, bpp(0)
{
	ilGenImages(1, &imageName);
	ilBindImage(imageName);
}

ImageFile::~ImageFile()
{
	ilDeleteImages(1, &imageName);
}

bool ImageFile::init(int width_, int height_, int bpp_)
{
	if(bpp_!=32)
		return false;

	width	= width_;
	height	= height_;
	bpp		= bpp_;

	Vector<char> data;
	data.resize(width*height*4);

	ilBindImage(imageName);

	return ilLoadDataL(&data[0], width*height*4, width, height, 1, bpp/8);
}

bool ImageFile::load(const char *filename_)
{
	ilBindImage(imageName);

	if( ilLoadImage(filename_) == IL_FALSE )
		return false;
	
	if( ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE) == IL_FALSE )
		return false;

	width	= ilGetInteger(IL_IMAGE_WIDTH);
	height	= ilGetInteger(IL_IMAGE_HEIGHT); 
	bpp		= ilGetInteger(IL_IMAGE_BPP) * 8;

	return true;
}

bool ImageFile::save(const char *filename_)
{
	ilBindImage(imageName);

	return ilSaveImage(filename_);
}

void ImageFile::setColor(int x, int y, const Color &rgba_)
{
	ilBindImage(imageName);

	ilSetPixels(x, y, 0, 1, 1, 1, IL_RGBA, IL_UNSIGNED_BYTE, (void *)(&rgba_) );
}

void ImageFile::setColor(int x, int y, const char *data_)
{
	ilBindImage(imageName);

	ilSetPixels(x, y, 0, width, height, 1, IL_RGBA, IL_UNSIGNED_BYTE, (void *)(data_) );
}

// getter
Color ImageFile::getColor(int x, int y) const
{
	ilBindImage(imageName);

	Color c;
	ilCopyPixels(x, y, 0, 1, 1, 1, IL_RGBA, IL_UNSIGNED_BYTE, (void *)&c);

	return c;
}

int ImageFile::getWidth() const
{
	return width;
}

int ImageFile::getHeight() const
{
	return height; 
}

int ImageFile::getBPP() const
{
	return bpp;
}

void ImageFile::clearColor(const Color &color)
{
	ilBindImage(imageName);

	for(int y=0; y<getHeight(); y++)
	{
		for(int x=0; x<getWidth(); x++)
		{
			setColor(x, y, color);
		}
	}
}