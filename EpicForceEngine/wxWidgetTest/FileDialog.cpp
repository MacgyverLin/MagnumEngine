#include "FileDialog.h"

FileDialog::FileDialog(const wxString & title)
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(300, 200))
{
	wxMenuBar *menubar = new wxMenuBar;
	wxMenu *file = new wxMenu;
	file->Append(wxID_OPEN, wxT("&Open"));
	menubar->Append(file, wxT("&File"));
	SetMenuBar(menubar);

	Connect(wxID_OPEN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(FileDialog::OnOpen));

	tc = new wxTextCtrl(this, -1, wxT(""), wxPoint(-1, -1), wxSize(-1, -1), wxTE_MULTILINE);

	Center();
}

void FileDialog::OnOpen(wxCommandEvent& event)
{
	wxFileDialog * fileDialog = new wxFileDialog(this);
    //fileDialog->SetFilename("1");
    //fileDialog->SetWildcard("*.bmp;*.png;*.tga");
    //fileDialog->SetFilterIndex(2);


	if (fileDialog->ShowModal() == wxID_OK)
	{
		wxString fileName = fileDialog->GetPath();
		tc->LoadFile(fileName);     
	}

	delete fileDialog;
}