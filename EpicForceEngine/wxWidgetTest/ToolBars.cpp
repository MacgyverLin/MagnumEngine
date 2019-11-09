#include "Toolbars.h"

Toolbars::Toolbars(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(280, 180))
{
	wxImage::AddHandler( new wxPNGHandler );

	wxBitmap exit(wxT("exit.png"), wxBITMAP_TYPE_PNG);
	wxBitmap newb(wxT("new.png"), wxBITMAP_TYPE_PNG);
	wxBitmap open(wxT("open.png"), wxBITMAP_TYPE_PNG);
	wxBitmap save(wxT("save.png"), wxBITMAP_TYPE_PNG);

	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

	toolbar1 = new wxToolBar(this, wxID_ANY);
	toolbar1->AddTool(wxID_ANY, newb, wxT(""));
	toolbar1->AddTool(wxID_ANY, open, wxT(""));
	toolbar1->AddTool(wxID_ANY, save, wxT(""));
	toolbar1->Realize();

	toolbar2 = new wxToolBar(this, wxID_ANY);
	toolbar2->AddTool(wxID_EXIT, exit, wxT("Exit application"));
	toolbar2->Realize();

	vbox->Add(toolbar1, 0, wxEXPAND);
	vbox->Add(toolbar2, 0, wxEXPAND);

	SetSizer(vbox);

	Connect(wxID_EXIT, wxEVT_COMMAND_TOOL_CLICKED, 
		wxCommandEventHandler(Toolbars::OnQuit));

	Centre();
}

void Toolbars::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}