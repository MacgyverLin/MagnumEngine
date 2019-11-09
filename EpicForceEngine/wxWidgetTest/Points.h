#ifndef _Points_h_
#define _Points_h_

#include "wxdef.h"

class Points : public wxFrame
{
public:
	Points(const wxString & title);

	void OnPaint(wxPaintEvent & event);
};

#endif