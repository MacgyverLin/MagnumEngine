#ifndef _ColorSelector2DWnd_h_
#define _ColorSelector2DWnd_h_

#include "wxdef.h"
#include "ColorSelector2DWndFiller.h"

class ColorSelector2DWnd : public wxPanel
{
public:
	ColorSelector2DWnd(wxPanel *parent, int id);
	~ColorSelector2DWnd();
private:
	void fillDC(wxMemoryDC &dc, wxBitmap &bitmap);
	void fillImage(wxImage &image);

	void onSize(wxSizeEvent& event);
	void onPaint(wxPaintEvent& event);  
private:
	ColorSelector2DWndFiller colorSelector2DWndFiller;

	unsigned char *buffer;
};

#endif