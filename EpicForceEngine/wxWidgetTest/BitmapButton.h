#ifndef _BitmapButton_h_
#define _BitmapButton_h_

#include "wxdef.h"

class BitmapButton : public wxFrame
{
public:
	BitmapButton(const wxString& title);

	wxSlider *slider;
	wxBitmapButton *button;
	int pos;

	void OnScroll(wxScrollEvent& event);

};

const int ID_SLIDER = 100;

#endif