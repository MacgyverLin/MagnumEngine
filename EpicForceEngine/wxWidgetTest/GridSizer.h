#ifndef _GridSizer_h_
#define _GridSizer_h_

#include "wxdef.h"

class GridSizer : public wxFrame
{
public:
	GridSizer(const wxString& title);

	wxMenuBar *menubar;
	wxMenu *file;

	wxBoxSizer *sizer;
	wxGridSizer *gs;
	wxTextCtrl *display;
};

#endif