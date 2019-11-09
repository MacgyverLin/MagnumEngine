#include "points.h"
#include <stdlib.h>
#include <time.h>

Points::Points(const wxString& title)
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(280, 180))
{
	this->Connect(wxEVT_PAINT, wxPaintEventHandler(Points::OnPaint));
	srand(time(NULL));
	this->Centre();
}

void Points::OnPaint(wxPaintEvent & event)
{
	wxPaintDC dc(this);

	wxCoord x = 0;
	wxCoord y = 0;

	wxSize size = this->GetSize();

	for (int i = 0; i<1000; i++) 
	{
		x = rand() % size.x + 1;
		y = rand() % size.y + 1;
		dc.DrawPoint(x, y);
	}
}