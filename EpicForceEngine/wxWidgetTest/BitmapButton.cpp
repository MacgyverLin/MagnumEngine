#include "bitmapbutton.h"

BitmapButton::BitmapButton(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(250, 130))
{
	wxImage::AddHandler( new wxPNGHandler );
	wxPanel *panel = new wxPanel(this);
	slider = new wxSlider(panel, ID_SLIDER, 0, 0, 100, 
		wxPoint(10, 30), wxSize(140, -1));

	button = new wxBitmapButton(panel, wxID_ANY, wxBitmap(wxT("mute.png"), 
		wxBITMAP_TYPE_PNG), wxPoint(180, 20));

	Connect(ID_SLIDER, wxEVT_COMMAND_SLIDER_UPDATED, 
		wxScrollEventHandler(BitmapButton::OnScroll));  
	Center();
}

void BitmapButton::OnScroll(wxScrollEvent& event)
{
	pos = slider->GetValue(); 

	if (pos == 0) 
	{
		button->SetBitmapLabel(wxBitmap(wxT("mute.png"), wxBITMAP_TYPE_PNG));
	}
	else if (pos > 0 && pos <= 30 ) 
	{
		button->SetBitmapLabel(wxBitmap(wxT("min.png"), wxBITMAP_TYPE_PNG));
	}
	else if (pos > 30 && pos < 80 ) 
	{
		button->SetBitmapLabel(wxBitmap(wxT("med.png"), wxBITMAP_TYPE_PNG));
	}
	else 
	{
		button->SetBitmapLabel(wxBitmap(wxT("max.png"), wxBITMAP_TYPE_PNG));
	}
}


