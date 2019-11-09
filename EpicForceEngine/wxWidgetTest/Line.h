#ifndef _Line_h_
#define _Line_h_

#include "wxdef.h"

class Line : public wxFrame
{
public:
    Line(const wxString& title);

    void OnPaint(wxPaintEvent& event);
};

#endif