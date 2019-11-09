#ifndef _FontDialog_h_
#define _FontDialog_h_

#include "wxdef.h"

class FontDialog : public wxFrame
{
public:
	FontDialog(const wxString& title);

	void OnOpen(wxCommandEvent& event);

	wxStaticText *st;
};

const int ID_FONTDIALOG = 1;

#endif