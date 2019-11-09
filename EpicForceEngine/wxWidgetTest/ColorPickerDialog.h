#ifndef _ColorPickerDialog_h_
#define _ColorPickerDialog_h_

#include "wxdef.h"

class ColorPickerDialog : public wxFrame
{
public:
	ColorPickerDialog(const wxString& title);
	~ColorPickerDialog();

	void OnScroll(wxScrollEvent& event);
	int GetCurWidth();
};

#endif