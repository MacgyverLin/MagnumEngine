#include "CheckBox.h"

CheckBox::CheckBox(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(270, 150))
{
	wxPanel *panel = new wxPanel(this, wxID_ANY);

	m_cb = new wxCheckBox(panel, ID_CHECKBOX, wxT("Show title"), 
		wxPoint(20, 20));
	m_cb->SetValue(true);
	Connect(ID_CHECKBOX, wxEVT_COMMAND_CHECKBOX_CLICKED, 
		wxCommandEventHandler(CheckBox::OnToggle));
	Centre();
}

void CheckBox::OnToggle(wxCommandEvent& WXUNUSED(event))
{
	if (m_cb->GetValue()) 
	{
		this->SetTitle(wxT("CheckBox"));
	} 
	else 
	{
		this->SetTitle(wxT(" "));
	}
}

