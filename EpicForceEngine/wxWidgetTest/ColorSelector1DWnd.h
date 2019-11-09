#ifndef _ColorSelector1DWnd_h_
#define _ColorSelector1DWnd_h_

#include "wxdef.h"
#include "ColorSelector1DWndFiller.h"

class ColorSelector1DWnd : public wxPanel
{
public:
	ColorSelector1DWnd(wxPanel *parent, int id);
	~ColorSelector1DWnd();
private:
	void fillDC(wxMemoryDC &dc, wxBitmap &bitmap);
	void fillImage(wxImage &image);

	void onSize(wxSizeEvent& event);
	void onPaint(wxPaintEvent& event);  
private:
	ColorSelector1DWndFiller colorSelector1DWndFiller;

	unsigned char *buffer;
};

#endif