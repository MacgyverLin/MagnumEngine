#ifndef _BitmapCreater_h_
#define _BitmapCreater_h_

#include "wxdef.h"

class BitmapCreater
{
public:
	static wxBitmap getBitmapFromMemory(const unsigned char *data, int length);
};

#endif