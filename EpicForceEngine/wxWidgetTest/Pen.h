#ifndef _Pen_h_
#define _Pen_h_

#include "wxdef.h"

class Pen : public wxFrame
{
public:
    Pen(const wxString& title);

    void OnPaint(wxPaintEvent& event);
};

#endif