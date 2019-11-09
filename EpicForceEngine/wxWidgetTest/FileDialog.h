#ifndef _FileDialog_h_
#define _FileDialog_h_

#include "wxdef.h"

class FileDialog : public wxFrame
{
public:
	FileDialog(const wxString& title);

	void OnOpen(wxCommandEvent& event);

	wxTextCtrl *tc;
};

#endif