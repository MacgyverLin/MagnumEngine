#include "burning.h"
#include "widget.h"

int ID_SLIDER = 1;

Burning::Burning(const wxString& title)
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(350, 200))
{
	cur_width = 75;

	wxPanel *panel = new wxPanel(this, wxID_ANY);
	wxPanel *centerPanel = new wxPanel(panel, wxID_ANY);

	m_slider = new wxSlider(centerPanel, ID_SLIDER, 75, 0, 750, wxPoint(-1, -1), 
		wxSize(150, -1), wxSL_LABELS);

	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *hbox3 = new wxBoxSizer(wxHORIZONTAL);

	m_wid = new Widget(panel, wxID_ANY);
	hbox->Add(m_wid, 1, wxEXPAND);

	hbox2->Add(centerPanel, 1, wxEXPAND);
	hbox3->Add(m_slider, 0, wxTOP | wxLEFT, 35);

	centerPanel->SetSizer(hbox3);

	vbox->Add(hbox2, 1, wxEXPAND);
	vbox->Add(hbox, 0, wxEXPAND);

	panel->SetSizer(vbox);
	m_slider->SetFocus();

	Connect(ID_SLIDER, wxEVT_COMMAND_SLIDER_UPDATED, 
		wxScrollEventHandler(Burning::OnScroll)); 

	Centre();
}

void Burning::OnScroll(wxScrollEvent& WXUNUSED(event))
{
	cur_width = m_slider->GetValue();
	m_wid->Refresh();
}

int Burning::GetCurWidth() 
{
	return cur_width;
}