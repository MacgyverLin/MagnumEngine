#include "pen.h"

Pen::Pen(const wxString& title)
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(360, 180))
{
	this->Connect(wxEVT_PAINT, wxPaintEventHandler(Pen::OnPaint));
	this->Centre();
}

void Pen::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);

	wxColour col1, col2;

	col1.Set(wxT("#0c0c0c"));
	col2.Set(wxT("#000000"));

	wxBrush brush(wxColour(255, 255, 255), wxTRANSPARENT);
	dc.SetBrush(brush);

	dc.SetPen(wxPen(col1, 1, wxSOLID));
	dc.DrawRectangle(10, 15, 90, 60);

	dc.SetPen(wxPen(col1, 1, wxDOT));
	dc.DrawRectangle(130, 15, 90, 60);

	dc.SetPen(wxPen(col1, 1, wxLONG_DASH));
	dc.DrawRectangle(250, 15, 90, 60);

	dc.SetPen(wxPen(col1, 1, wxSHORT_DASH));
	dc.DrawRectangle(10, 105, 90, 60);

	dc.SetPen(wxPen(col1, 1, wxDOT_DASH));
	dc.DrawRectangle(130, 105, 90, 60);

	dc.SetPen(wxPen(col1, 1, wxTRANSPARENT));
	dc.DrawRectangle(250, 105, 90, 60);
}