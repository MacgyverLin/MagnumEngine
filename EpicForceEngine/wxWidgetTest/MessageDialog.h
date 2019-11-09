#ifndef _MessageDialog_h_
#define _MessageDialog_h_

#include "wxdef.h"

class MessageDialog : public wxFrame
{
public:
	MessageDialog(const wxString& title);

	void ShowMessage1(wxCommandEvent & event);
	void ShowMessage2(wxCommandEvent & event);
	void ShowMessage3(wxCommandEvent & event);
	void ShowMessage4(wxCommandEvent & event);
};

const int ID_INFO = 1;
const int ID_ERROR = 2;
const int ID_QUESTION = 3;
const int ID_ALERT = 4;

#endif