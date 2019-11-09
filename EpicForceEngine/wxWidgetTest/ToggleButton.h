#ifndef _ToggleButton_h_
#define _ToggleButton_h_

#include "wxdef.h"

class ToggleButton : public wxFrame
{
public:
	ToggleButton(const wxString& title);

	void OnToggleRed(wxCommandEvent& event);
	void OnToggleGreen(wxCommandEvent& event);
	void OnToggleBlue(wxCommandEvent& event);

protected:
	wxToggleButton *m_tgbutton1;
	wxToggleButton *m_tgbutton2;
	wxToggleButton *m_tgbutton3;

	wxPanel *m_panel;
	wxColour *colour;

};

const int ID_TGBUTTON1 = 101;
const int ID_TGBUTTON2 = 102;
const int ID_TGBUTTON3 = 103;

#endif