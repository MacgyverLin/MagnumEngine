#include "TGAFile.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "assert.h"
using namespace EpicForce;

/////////////////////////////////////////////////////////////
TGAFile::TGAFile() 
: pixels(0)
, index(0)
{
	memset(&header, 0, sizeof(header));
}

TGAFile::~TGAFile()
{
	if(pixels)
		delete [] pixels;
	if(index)
		delete [] index;
}

bool TGAFile::init(int width, int height, int bpp)
{
	if(bpp==32 || bpp==24)
	{
		header.identsize		= 0;		// size of ID field that follows 18 byte header (0 usually)
		header.colourmaptype	= 0;		// type of colour map 0=none, 1=has palette
		header.imagetype		= 2;		// type of image 0=none,1=indexed,2=rgb,3=grey,+8=rle packed

		header.colourmapstart	= 0;		// first colour map entry in palette
		header.colourmaplength	= 0;		// number of colours in palette
		header.colourmapbits	= 0;		// number of bits per palette entry 15,16,24,32

		header.xstart			= 0;		// image x origin
		header.ystart			= 0;		// image y origin
		header.width			= width;	// image width in pixels
		header.height			= height;	// image height in pixels
		header.bits				= bpp;		// image bits per pixel 8,16,24,32
		header.descriptor		= 8;		// image descriptor bits (vh flip bits)

		if(index)
			delete [] index;
		if(pixels)
			delete [] pixels;
		pixels = new Color[header.height*header.width];
		for(int i=0; i<header.height*header.width; i++)
		{
			pixels[i].R() = 0xff;
			pixels[i].G() = 0xff;
			pixels[i].B() = 0xff;
			pixels[i].A() = 0x00;
		}
	}
	else if(bpp==8)
	{
		header.identsize		= 0;		// size of ID field that follows 18 byte header (0 usually)
		header.colourmaptype	= 1;		// type of colour map 0=none, 1=has palette
		header.imagetype		= 1;		// type of image 0=none,1=indexed,2=rgb,3=grey,+8=rle packed

		header.colourmapstart	= 0;		// first colour map entry in palette
		header.colourmaplength	= 256;		// number of colours in palette
		header.colourmapbits	= 24;		// number of bits per palette entry 15,16,24,32

		header.xstart			= 0;		// image x origin
		header.ystart			= 0;		// image y origin
		header.width			= width;	// image width in pixels
		header.height			= height;	// image height in pixels
		header.bits				= bpp;		// image bits per pixel 8,16,24,32
		header.descriptor		= 8;		// image descriptor bits (vh flip bits)

		if(index)
			delete [] index;
		if(pixels)
			delete [] pixels;

		index = new unsigned char[header.height*header.width];

		for(int i=header.colourmapstart; i<header.colourmapstart+header.colourmaplength; i++)
		{
			palette[i][0] = 0x00;
			palette[i][1] = 0x00;
			palette[i][2] = 0x00;
			palette[i][3] = 0xff;
		}
	}
		
	return true;
}

bool TGAFile::load(const char *filename_)
{
	FileInputStream is(filename_);
	if(!is.opened())
		return false;

	is >> *this;

	if(header.imagetype != 1 && header.imagetype != 2)
	{
		printf("Error: Only supports uncompressed 8 bit indexed or uncompressed 24/32-bit RGBA format TGA\n");
		return false;
	}

	return true;
}

bool TGAFile::save(const char *filename_)
{
	FileOutputStream os(filename_);

	os << *this;

	return true;
}

void TGAFile::read(InputStream &is)
{
	is >> header.identsize;			// size of ID field that follows 18 byte header (0 usually)
	is >> header.colourmaptype;		// type of colour map 0=none, 1=has palette
	is >> header.imagetype;			// type of image 0=none,1=indexed,2=rgb,3=grey,+8=rle packed

	is >> header.colourmapstart;		// first colour map entry in palette
	is >> header.colourmaplength;		// number of colours in palette
	is >> header.colourmapbits;		// number of bits per palette entry 15,16,24,32

	is >> header.xstart;				// image x origin
	is >> header.ystart;				// image y origin
	is >> header.width;				// image width in pixels
	is >> header.height;				// image height in pixels
	is >> header.bits;					// image bits per pixel 8,16,24,32
	is >> header.descriptor;			// image descriptor bits (vh flip bits)

	if(header.bits==32)
		load32BitRGBA(is);
	else if(header.bits==24)
		load24BitRGBA(is);
	else if(header.bits==8)
		load8BitIndex(is);
	else
		assert(0);
}

void TGAFile::load32BitRGBA(InputStream &is)
{
	if(pixels)
		delete [] pixels;
	if(index)
		delete [] index;
	
	is.skip(header.identsize);

	pixels = new Color[header.height*header.width];

	for(int i=0; i<header.height*header.width; i++)
	{
		is >> pixels[i][2];
		is >> pixels[i][1];
		is >> pixels[i][0];
		is >> pixels[i][3];
	}
}

void TGAFile::load24BitRGBA(InputStream &is)
{
	if(pixels)
		delete [] pixels;
	if(index)
		delete [] index;
	
	is.skip(header.identsize);

	pixels = new Color[header.height*header.width];

	for(int i=0; i<header.height*header.width; i++)
	{
		is >> pixels[i][2];
		is >> pixels[i][1];
		is >> pixels[i][0];
		pixels[i][3] = 0xff;
	}
}

void TGAFile::load8BitIndex(InputStream &is)
{
	if(pixels)
		delete [] pixels;
	if(index)
		delete [] index;
	
	is.skip(header.identsize);

	for(int i=header.colourmapstart; i<header.colourmapstart+header.colourmaplength; i++)
	{
		is >> palette[i][2];
		is >> palette[i][1];
		is >> palette[i][0];
		palette[i][3] = 0xff;
	}

	index = new unsigned char[header.height*header.width];
	is.readX(index, sizeof(unsigned char) * header.height*header.width);
}

void TGAFile::write(OutputStream &os) const
{
	if(header.bits==32)
		return save32BitRGBA(os);
	else if(header.bits==24)
		return save24BitRGBA(os);
	else if(header.bits==8)
		return save8BitIndex(os);
	else
		assert(0);
}

void TGAFile::save32BitRGBA(OutputStream &os) const
{
	assert(pixels);

	os.writeX(&header, 1*sizeof(header));

	for(int i=0; i<header.height*header.width; i++)
	{
		os << pixels[i][2];
		os << pixels[i][1];
		os << pixels[i][0];
		os << pixels[i][3];
	}
}

void TGAFile::save24BitRGBA(OutputStream &os) const
{
	assert(pixels);

	os.writeX(&header, 1*sizeof(header));

	for(int i=0; i<header.height*header.width; i++)
	{
		os << pixels[i][2];
		os << pixels[i][1];
		os << pixels[i][0];
		//os << pixels[i][3];
	}
}

void TGAFile::save8BitIndex(OutputStream &os) const
{
	assert(index);

	os.writeX(&header, 1*sizeof(header));

	for(int i=header.colourmapstart; i<header.colourmapstart+header.colourmaplength; i++)
	{
		os << palette[i][2];
		os << palette[i][1];
		os << palette[i][0];
	}

	os.writeX(index, sizeof(unsigned char)*header.height*header.width);
}

void TGAFile::setColor(int x, int y, const Color &rgba_)
{
	assert(header.bits==32 || header.bits==24);

	Color *line = getColorRow(y);
	line[x] = rgba_;
}

void TGAFile::setIndex(int x, int y, unsigned char index_)
{
	assert(header.bits==8);
	
	unsigned char *line = getIndexRow(y);

	line[x] = index_;
}

void TGAFile::setPalette(int i, const Color &rgba_)
{
	assert(i>=0 && i<256);
	assert(header.bits==8);
	
	palette[i] = rgba_;
}

// getter
Color TGAFile::getColor(int x, int y) const
{
	assert(header.bits==32 || header.bits==24);

	const Color *line = getColorRow(y);
	return line[x];
}

unsigned char TGAFile::getIndex(int x, int y) const
{
	assert(header.bits==8);
	
	const unsigned char *line = getIndexRow(y);
	return line[x];
}

Color TGAFile::getPalette(int i) const
{
	assert(i>=0 && i<256);
	assert(header.bits==8);

	return palette[i];
}

int TGAFile::getWidth() const
{
	return header.width;
}

int TGAFile::getHeight() const
{
	return header.height;
}

int TGAFile::getBPP() const
{
	return header.bits;
}

void TGAFile::clearColor(const Color &color)
{
	for(int y=0; y<getHeight(); y++)
	{
		for(int x=0; x<getWidth(); x++)
		{
			setColor(x, y, color);
		}
	}
}

void TGAFile::clearIndex(unsigned char idx)
{
	for(int y=0; y<getHeight(); y++)
	{
		for(int x=0; x<getWidth(); x++)
		{
			setIndex(x, y, idx);
		}
	}
}

Color *TGAFile::getColorRow(int y) const
{
	int idx = (getHeight() - 1 - y) * getWidth();

	return &(pixels[idx]);
}

unsigned char *TGAFile::getIndexRow(int y) const
{
	int idx = (getHeight() - 1 - y) * getWidth();

	return &(index[idx]);
}

Color *TGAFile::getDataPtr() const
{
	return &(pixels[0]);
}