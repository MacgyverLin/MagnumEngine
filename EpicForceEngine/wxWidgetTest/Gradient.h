#ifndef _Gradient_h_
#define _Gradient_h_

#include "wxdef.h"

class Gradient : public wxFrame
{
public:
	Gradient(const wxString& title);

	void OnPaint(wxPaintEvent& event);
};

#endif