#include "gradient.h"

Gradient::Gradient(const wxString& title)
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(220, 260))
{
	this->Connect(wxEVT_PAINT, wxPaintEventHandler(Gradient::OnPaint));
	this->Centre();
}

void Gradient::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);

	wxColour col1, col2;

	col1.Set(wxT("#e12223"));
	col2.Set(wxT("#000000"));

	dc.GradientFillLinear(wxRect(20, 20, 180, 40), col1, col2, wxNORTH);
	dc.GradientFillLinear(wxRect(20, 80, 180, 40), col1, col2, wxSOUTH);
	dc.GradientFillLinear(wxRect(20, 140, 180, 40), col1, col2, wxEAST);
	dc.GradientFillLinear(wxRect(20, 200, 180, 40), col1, col2, wxWEST);  
}
