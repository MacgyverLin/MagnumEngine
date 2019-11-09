#ifndef _ImageFile_h_
#define _ImageFile_h_

#include "stdio.h"
#include "Color.h"
using namespace std;

namespace EpicForce
{
	
class ImageFile
{
public:
	ImageFile();
	~ImageFile();

	bool init(int width, int height, int bpp);
	bool load(const char *filename_);
	bool save(const char *filename_);

// setter
	void setColor(int x, int y, const Color &rgba_);
	void setColor(int x, int y, const char *data_);
// getter
	Color getColor(int x, int y) const;

	int getWidth() const;
	int getHeight() const;
	int getBPP() const;
// op
	void clearColor(const Color &color);
private:
	unsigned int imageName;
	int width, height, bpp;
};

};

#endif