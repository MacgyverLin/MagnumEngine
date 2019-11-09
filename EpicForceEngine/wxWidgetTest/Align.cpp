#include "align.h"

Align::Align(const wxString& title)
: wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(300, 200))
{
	wxPanel *panel = new wxPanel(this, -1);
	wxButton *ok = new wxButton(panel, -1, wxT("Ok"));
	wxButton *cancel = new wxButton(panel, -1, wxT("Cancel"));

	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);

	panel->SetSizer(vbox);
	vbox->Add(hbox1, 1, wxEXPAND);
	vbox->Add(hbox2, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 10);
		hbox1->Add(new wxPanel(panel, -1));
		hbox2->Add(ok);
		hbox2->Add(cancel);

	Centre();
}