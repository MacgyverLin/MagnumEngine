#include "line.h"

Line::Line(const wxString& title)
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(280, 180))
{
	this->Connect(wxEVT_PAINT, wxPaintEventHandler(Line::OnPaint));
	this->Centre();
}

void Line::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);

	wxCoord x1 = 50, y1 = 60;
	wxCoord x2 = 190, y2 = 60;

	dc.DrawLine(x1, y1, x2, y2);
}
