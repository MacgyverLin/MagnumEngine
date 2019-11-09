#ifndef _Toolbar_h_
#define _Toolbar_h_

#include "wxdef.h"

class Toolbar : public wxFrame
{
public:
    Toolbar(const wxString& title);

    void OnQuit(wxCommandEvent& event);
};

#endif