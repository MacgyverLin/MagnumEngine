#include "SimpleMenu.h"

SimpleMenu::SimpleMenu(const wxString& title)
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(280, 180))
{
	menubar = new wxMenuBar;
	file = new wxMenu;
	
	SetMenuBar(menubar);
		menubar->Append(file, wxT("&File"));
			file->Append(wxID_EXIT, wxT("&Quit"));

	Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(SimpleMenu::OnQuit));
	Centre();
}

void SimpleMenu::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}