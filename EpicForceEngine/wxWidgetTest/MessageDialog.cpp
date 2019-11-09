#include "MessageDialog.h"

MessageDialog::MessageDialog(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(210, 110))
{

	wxPanel *panel = new wxPanel(this, wxID_ANY);

	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
	wxGridSizer *gs = new wxGridSizer(2, 2, 2, 2);

	wxButton *btn1 = new wxButton(panel, ID_INFO, wxT("Info"));
	wxButton *btn2 = new wxButton(panel, ID_ERROR, wxT("Error"));
	wxButton *btn3 = new wxButton(panel, ID_QUESTION, wxT("Question"));
	wxButton *btn4 = new wxButton(panel, ID_ALERT, wxT("Alert"));

	Connect(ID_INFO, wxEVT_COMMAND_BUTTON_CLICKED,		wxCommandEventHandler(MessageDialog::ShowMessage1));
	Connect(ID_ERROR, wxEVT_COMMAND_BUTTON_CLICKED,		wxCommandEventHandler(MessageDialog::ShowMessage2));
	Connect(ID_QUESTION, wxEVT_COMMAND_BUTTON_CLICKED, 	wxCommandEventHandler(MessageDialog::ShowMessage3));
	Connect(ID_ALERT, wxEVT_COMMAND_BUTTON_CLICKED, 	wxCommandEventHandler(MessageDialog::ShowMessage4));

	gs->Add(btn1, 1, wxEXPAND);
	gs->Add(btn2, 1);
	gs->Add(btn3, 1);
	gs->Add(btn4, 1);

	hbox->Add(gs, 0, wxALL, 15);
	panel->SetSizer(hbox);

	Center();
}

void MessageDialog::ShowMessage1(wxCommandEvent& event) 
{
	wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Download completed"), wxT("Info"), wxOK);

	dial->ShowModal();
}

void MessageDialog::ShowMessage2(wxCommandEvent& event) 
{
	wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Error loading file"), wxT("Error"), wxOK | wxICON_ERROR);

	dial->ShowModal();
}

void MessageDialog::ShowMessage3(wxCommandEvent& event) 
{
	wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Are you sure to quit?"), wxT("Question"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);
	
	dial->ShowModal();
}

void MessageDialog::ShowMessage4(wxCommandEvent& event) 
{
	wxMessageDialog *dial = new wxMessageDialog(NULL, wxT("Unallowed operation"), wxT("Exclamation"), wxOK | wxICON_EXCLAMATION);

	dial->ShowModal();
}