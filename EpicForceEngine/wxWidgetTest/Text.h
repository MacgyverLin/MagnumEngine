#ifndef _Text_h_
#define _Text_h_

#include "wxdef.h"

class Text : public wxFrame
{
public:
    Text(const wxString & title);

    void OnPaint(wxPaintEvent & event);

};

#endif