#include "ColorSelector2DWnd.h"

ColorSelector2DWnd::ColorSelector2DWnd(wxPanel *parent, int id)
: wxPanel(parent, id, wxDefaultPosition, wxSize(256, 256), wxSUNKEN_BORDER)
{
	wxSize size = GetSize();

	buffer = new unsigned char[size.x * size.y * 4];

	colorSelector2DWndFiller.construct(size.x, size.y, buffer);

	Connect(wxEVT_PAINT, wxPaintEventHandler(ColorSelector2DWnd::onPaint));
	Connect(wxEVT_SIZE , wxSizeEventHandler(ColorSelector2DWnd::onSize));
}

ColorSelector2DWnd::~ColorSelector2DWnd()
{
	if(buffer)
	{
		delete[] buffer;
		buffer = 0;
	}
}

void ColorSelector2DWnd::fillDC(wxMemoryDC &dc, wxBitmap &bitmap)
{
	wxSize size = GetSize();

	for(int y=0; y<size.y; y++)
	{
		for(int x=0; x<size.x; x++)
		{
			dc.SetPen(wxPen(wxColour(x, y, 0))); 
			dc.DrawPoint(x, y);
		}
	}
}

void ColorSelector2DWnd::fillImage(wxImage &image)
{
	float red   = 0.9f;
	float green = 0.2f;
	float blue  = 1.0f;

	colorSelector2DWndFiller.setRedMode  (red);
	colorSelector2DWndFiller.setGreenMode(green);
	colorSelector2DWndFiller.setBlueMode (blue);

	float hue = 0.9f;
	float sat = 0.2f;
	float val = 1.0f;
	colorSelector2DWndFiller.setHueMode(hue);
	colorSelector2DWndFiller.setSatMode(sat);
	colorSelector2DWndFiller.setValMode(val);
}

void ColorSelector2DWnd::onPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);

	wxSize size = GetSize();

	dc.SetPen(wxPen(wxColour(255, 255, 184))); 
	dc.SetBrush(wxBrush(wxColour(255, 255, 184)));
	dc.DrawRectangle(0, 0, size.x, size.y);

	dc.SetPen(wxPen(wxColour(0, 0, 0))); 
	dc.SetBrush(wxBrush(wxColour(255, 255, 255)));
	dc.DrawArc(140, 100, 100, 100, 120, 120);
	dc.DrawCircle(30, 30, 40);

	wxImage image(size.x, size.y, (unsigned char *)buffer, true);
	fillImage(image);
	wxBitmap bitmap(image.Mirror(), 32);
	dc.DrawBitmap(bitmap, 0, 0);
}

void ColorSelector2DWnd::onSize(wxSizeEvent& event)
{
	Refresh();
}