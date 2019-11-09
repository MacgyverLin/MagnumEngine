#ifndef _BoxSizer_h_
#define _BoxSizer_h_

#include "wxdef.h"

class BoxSizer : public wxFrame
{
public:
	BoxSizer(const wxString& title);

	wxMenuBar *menubar;
	wxMenu *file;
	wxMenu *edit;
	wxMenu *help;
	wxTextCtrl *textctrl;

};

#endif