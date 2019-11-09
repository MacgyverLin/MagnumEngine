#ifndef _Regions_h_
#define _Regions_h_

#include "wxdef.h"

class Regions : public wxFrame
{
public:
	Regions(const wxString & title);

	void OnPaint(wxPaintEvent & event);
};

#endif