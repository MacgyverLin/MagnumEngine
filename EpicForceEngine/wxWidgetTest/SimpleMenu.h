#ifndef _SimpleMenu_h_
#define _SimpleMenu_h_

#include "wxdef.h"

class SimpleMenu : public wxFrame
{
public:
    SimpleMenu(const wxString& title);

    void OnQuit(wxCommandEvent& event);

    wxMenuBar *menubar;
    wxMenu *file;

};

#endif