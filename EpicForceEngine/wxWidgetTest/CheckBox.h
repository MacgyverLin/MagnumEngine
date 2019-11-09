#ifndef _CheckBox_h_
#define _CheckBox_h_

#include "wxdef.h"

class CheckBox : public wxFrame
{
public:
    CheckBox(const wxString& title);

    void OnToggle(wxCommandEvent& event);

    wxCheckBox *m_cb;
};

const int ID_CHECKBOX = 100;

#endif