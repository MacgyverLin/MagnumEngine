#include "FlexGridSizer.h"

FlexGridSizer::FlexGridSizer(const wxString& title)
	: wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(270, 220))
{ 
	wxPanel *panel			= new wxPanel(this, -1);
	wxBoxSizer *hbox		= new wxBoxSizer(wxHORIZONTAL);
	wxFlexGridSizer *fgs	= new wxFlexGridSizer(3, 2, 9, 25);

	wxStaticText *thetitle	= new wxStaticText(panel, -1, wxT("Title"));
	wxStaticText *author	= new wxStaticText(panel, -1, wxT("Author"));
	wxStaticText *review	= new wxStaticText(panel, -1, wxT("Review"));

	wxTextCtrl *tc1			= new wxTextCtrl(panel, -1);
	wxTextCtrl *tc2			= new wxTextCtrl(panel, -1);
	wxTextCtrl *tc3			= new wxTextCtrl(panel, -1, wxT(""), 
											 wxPoint(-1, -1), wxSize(-1, -1), wxTE_MULTILINE);

	panel->SetSizer(hbox);
		hbox->Add(fgs, 1, wxALL | wxEXPAND, 15);
			fgs->Add(thetitle);
			fgs->Add(tc1, 1, wxEXPAND);
			fgs->Add(author);
			fgs->Add(tc2, 1, wxEXPAND);
			fgs->Add(review, 1, wxEXPAND);
			fgs->Add(tc3, 1, wxEXPAND);

			fgs->AddGrowableRow(2, 1);
			fgs->AddGrowableCol(1, 1);

	Centre();
}