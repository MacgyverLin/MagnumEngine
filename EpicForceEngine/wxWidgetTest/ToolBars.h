#ifndef _Toolbars_h_
#define _Toolbars_h_

#include "wxdef.h"

class Toolbars : public wxFrame
{
public:
	Toolbars(const wxString& title);

	void OnQuit(wxCommandEvent& event);

	wxToolBar *toolbar1;
	wxToolBar *toolbar2;
};

#endif