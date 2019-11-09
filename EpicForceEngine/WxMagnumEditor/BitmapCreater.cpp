#include "BitmapCreater.h"

wxBitmap BitmapCreater::getBitmapFromMemory(const unsigned char *data, int length) 
{
	wxMemoryInputStream is(data, length);

	return wxBitmap(wxImage(is, wxBITMAP_TYPE_ANY, -1), -1);
}