#include "Border.h"

Border::Border(const wxString& title)
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(250, 200))
{
	wxColour col1, col2;
	col1.Set(wxT("#4f5049"));
	col2.Set(wxT("#ededed"));

	wxPanel *panel = new wxPanel(this, -1);
		panel->SetBackgroundColour(col1);
	wxPanel *midPan = new wxPanel(panel, wxID_ANY);
		midPan->SetBackgroundColour(col2);

	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	panel->SetSizer(vbox);
	vbox->Add(midPan, 1, wxEXPAND | wxALL, 20);
	
	Centre();
}