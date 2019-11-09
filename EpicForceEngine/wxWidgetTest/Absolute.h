#ifndef _Absolute_h_
#define _Absolute_h_

#include "wxdef.h"

class Absolute : public wxFrame
{
public:
	Absolute(const wxString& title);

	wxMenuBar *menubar;
	wxMenu *file;
	wxMenu *edit;
	wxMenu *help;
	wxTextCtrl *textctrl;
};

#endif