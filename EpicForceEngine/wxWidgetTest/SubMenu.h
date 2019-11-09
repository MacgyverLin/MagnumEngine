#ifndef _SubMenu_h_
#define _SubMenu_h_

#include "wxdef.h"

class SubMenu : public wxFrame
{
public:
	SubMenu(const wxString& title);

	void OnQuit(wxCommandEvent & event);

	wxMenuBar *menubar;
	wxMenu *file;
	wxMenu *imp;
	wxMenuItem *quit;

};

#endif