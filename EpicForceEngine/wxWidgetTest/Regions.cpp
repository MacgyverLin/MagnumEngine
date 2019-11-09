#include "Regions.h"


Regions::Regions(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(270, 220))
{
	this->Connect(wxEVT_PAINT, wxPaintEventHandler(Regions::OnPaint));
	this->Centre();
}

void Regions::OnPaint(wxPaintEvent & event)
{
	wxPaintDC dc(this);
	wxColour gray, white, red, blue;
	wxColour orange, green, brown;

	gray.Set(wxT("#d4d4d4"));
	white.Set(wxT("#ffffff"));
	red.Set(wxT("#ff0000"));
	orange.Set(wxT("#fa8e00"));
	green.Set(wxT("#619e1b"));
	brown.Set(wxT("#715b33"));
	blue.Set(wxT("#0d0060"));

	dc.SetPen(wxPen(gray));

	dc.DrawRectangle(20, 20, 50, 50);
	dc.DrawRectangle(30, 40, 50, 50);

	dc.SetBrush(wxBrush(white));
	dc.DrawRectangle(100, 20, 50, 50);
	dc.DrawRectangle(110, 40, 50, 50); 
	wxRegion region1(100, 20, 50, 50);
	wxRegion region2(110, 40, 50, 50);
	region1.Intersect(region2);
	wxRect rect1 = region1.GetBox();
	dc.SetClippingRegion(region1);
	dc.SetBrush(wxBrush(red));
	dc.DrawRectangle(rect1);
	dc.DestroyClippingRegion();

	dc.SetBrush(wxBrush(white));
	dc.DrawRectangle(180, 20, 50, 50);
	dc.DrawRectangle(190, 40, 50, 50);
	wxRegion region3(180, 20, 50, 50);
	wxRegion region4(190, 40, 50, 50);
	region3.Union(region4);
	dc.SetClippingRegion(region3);
	wxRect rect2 = region3.GetBox();
	dc.SetBrush(wxBrush(orange));
	dc.DrawRectangle(rect2);
	dc.DestroyClippingRegion();

	dc.SetBrush(wxBrush(white));
	dc.DrawRectangle(20, 120, 50, 50);
	dc.DrawRectangle(30, 140, 50, 50);
	wxRegion region5(20, 120, 50, 50);
	wxRegion region6(30, 140, 50, 50);
	region5.Xor(region6);
	wxRect rect3 = region5.GetBox();
	dc.SetClippingRegion(region5);
	dc.SetBrush(wxBrush(green));
	dc.DrawRectangle(rect3);
	dc.DestroyClippingRegion();

	dc.SetBrush(wxBrush(white));
	dc.DrawRectangle(100, 120, 50, 50);
	dc.DrawRectangle(110, 140, 50, 50);
	wxRegion region7(100, 120, 50, 50);
	wxRegion region8(110, 140, 50, 50);
	region7.Subtract(region8);
	wxRect rect4 = region7.GetBox();
	dc.SetClippingRegion(region7);
	dc.SetBrush(wxBrush(brown));
	dc.DrawRectangle(rect4);
	dc.DestroyClippingRegion();

	dc.SetBrush(white);
	dc.DrawRectangle(180, 120, 50, 50);
	dc.DrawRectangle(190, 140, 50, 50);
	wxRegion region9(180, 120, 50, 50);
	wxRegion region10(190, 140, 50, 50);
	region10.Subtract(region9);
	wxRect rect5 = region10.GetBox();
	dc.SetClippingRegion(region10);
	dc.SetBrush(wxBrush(blue));
	dc.DrawRectangle(rect5);
	dc.DestroyClippingRegion(); 
}
