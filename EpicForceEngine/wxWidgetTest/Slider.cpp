#include "Slider.h"

Slider::Slider(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, 
	wxSize(270, 200))
{
	panel = new MyPanel(this);
	Center();
}


MyPanel::MyPanel(wxFrame * parent)
	: wxPanel(parent, wxID_ANY)
{
	fill = 0;
	slider = new wxSlider(this, ID_SLIDER, 0, 0, 140, wxPoint(50, 30), 
		wxSize(-1, 140), wxSL_VERTICAL);

	Connect(ID_SLIDER, wxEVT_COMMAND_SLIDER_UPDATED, 
		wxScrollEventHandler(MyPanel::OnScroll));  
	Connect(wxEVT_PAINT, wxPaintEventHandler(MyPanel::OnPaint));

}

void MyPanel::OnScroll(wxScrollEvent& event)
{
	fill = slider->GetValue();
	Refresh();
}

void MyPanel::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);

	wxPen pen(wxColour(212, 212, 212));
	dc.SetPen(pen);

	dc.DrawRectangle(wxRect(140, 30, 80, 140));  

	wxBrush brush1(wxColour(197, 108, 0));
	dc.SetBrush(brush1);

	dc.DrawRectangle(wxRect(140, 30, 80, fill));
}

