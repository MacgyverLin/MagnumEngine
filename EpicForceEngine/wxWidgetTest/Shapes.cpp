#include "shapes.h"

Shapes::Shapes(const wxString& title)
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(350, 300))
{
	this->Connect(wxEVT_PAINT, wxPaintEventHandler(Shapes::OnPaint));
	this->Centre();
}

void Shapes::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);

	wxPoint lines[] = { wxPoint(20, 260), wxPoint(100, 260), 
		wxPoint(20, 210), wxPoint(100, 210) };
	wxPoint polygon[] = { wxPoint(130, 140), wxPoint(180, 170), 
		wxPoint(180, 140), wxPoint(220, 110), wxPoint(140, 100) };
	wxPoint splines[] = { wxPoint(240, 170), wxPoint(280, 170), 
		wxPoint(285, 110), wxPoint(325, 110) };

	dc.DrawEllipse(20, 20, 90, 60);
	dc.DrawRoundedRectangle(130, 20, 90, 60, 10);
	dc.DrawArc(240, 40, 340, 40, 290, 20);

	dc.DrawPolygon(4, polygon);
	dc.DrawRectangle(20, 120, 80, 50);
	dc.DrawSpline(4, splines);

	dc.DrawLines(4, lines);
	dc.DrawCircle(170, 230, 35);
	dc.DrawRectangle(250, 200, 60, 60);
}

