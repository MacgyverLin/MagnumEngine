#ifndef _Button_h_
#define _Button_h_

#include "wxdef.h"

class Button : public wxFrame
{
public:
    Button(const wxString& title);

    void OnQuit(wxCommandEvent & event);
};

#endif