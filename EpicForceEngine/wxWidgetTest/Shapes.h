#ifndef _Shapes_h_
#define _Shapes_h_

#include "wxdef.h"

class Shapes : public wxFrame
{
public:
	Shapes(const wxString & title);

	void OnPaint(wxPaintEvent & event);
};

#endif