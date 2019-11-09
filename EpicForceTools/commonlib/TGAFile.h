#ifndef _TGAFile_h_
#define _TGAFile_h_

#include "stdio.h"
#include "Color.h"
#include <map>
#include "InputStream.h"
#include "OutputStream.h"
using namespace std;

namespace EpicForce
{

class TGAFile
{
public:
	class TGAHeader
	{
	public:
		unsigned char identsize;			// size of ID field that follows 18 byte header (0 usually)
	    unsigned char colourmaptype;		// type of colour map 0=none, 1=has palette
	    unsigned char imagetype;			// type of image 0=none,1=indexed,2=rgb,3=grey,+8=rle packed

	    short colourmapstart;				// first colour map entry in palette
	    short colourmaplength;				// number of colours in palette
	    unsigned char colourmapbits;		// number of bits per palette entry 15,16,24,32

	    short xstart;						// image x origin
	    short ystart;						// image y origin
	    short width;						// image width in pixels
	    short height;						// image height in pixels
	    unsigned char bits;					// image bits per pixel 8,16,24,32
	    unsigned char descriptor;			// image descriptor bits (vh flip bits)
	};
	TGAFile();
	~TGAFile();

	bool init(int width, int height, int bpp);
	bool load(const char *filename_);
	bool save(const char *filename_);
	
	void read(InputStream &is);
	void write(OutputStream &os) const;
// setter
	void setColor(int x, int y, const Color &rgba_);
	void setIndex(int x, int y, unsigned char index_);
	void setPalette(int i, const Color &rgba_);
// getter
	Color getColor(int x, int y) const;
	unsigned char getIndex(int x, int y) const;
	Color getPalette(int i) const;
	int getWidth() const;
	int getHeight() const;
	int getBPP() const;
// op
	void clearColor(const Color &color);
	void clearIndex(unsigned char idx);

	Color *getColorRow(int y) const;
	unsigned char *getIndexRow(int y) const;

	Color *getDataPtr() const;
private:
	void load32BitRGBA(InputStream &is);
	void load24BitRGBA(InputStream &is);
	void load8BitIndex(InputStream &is);
	void save32BitRGBA(OutputStream &os) const;
	void save24BitRGBA(OutputStream &os) const;
	void save8BitIndex(OutputStream &os) const;
	
	TGAHeader		header;
	Color			*pixels;

	Color			palette[256];
	unsigned char	*index;
};

};

#endif