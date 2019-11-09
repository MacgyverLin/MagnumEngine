#include "ColorPickerDialog.h"
#include "ColorSelector2DWnd.h"
#include "ColorSelector1DWnd.h"

ColorPickerDialog::ColorPickerDialog(const wxString& title)
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(480, 480))
{
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);

	wxPanel *panel = new wxPanel(this, wxID_ANY);
	wxPanel *centerPanel = new wxPanel(panel, wxID_ANY);

	ColorSelector2DWnd *colorSelector2DWnd = new ColorSelector2DWnd(panel, wxID_ANY);
	ColorSelector1DWnd *colorSelector1DWnd = new ColorSelector1DWnd(panel, wxID_ANY);
	panel->SetSizer(vbox);
		vbox->Add(hbox, 1, wxEXPAND);
			hbox->Add(centerPanel, 1, wxEXPAND);
		vbox->Add(hbox2, 0);
			hbox2->Add(colorSelector2DWnd, 0);
			hbox2->Add(32, -1, 0);
			hbox2->Add(colorSelector1DWnd, 0);

	Connect(wxEVT_COMMAND_SLIDER_UPDATED,  wxScrollEventHandler(ColorPickerDialog::OnScroll)); 

	Centre();
}

ColorPickerDialog::~ColorPickerDialog()
{
}

void ColorPickerDialog::OnScroll(wxScrollEvent& WXUNUSED(event))
{
	// cur_width = m_slider->GetValue();
	// m_wid->Refresh();
}

int ColorPickerDialog::GetCurWidth() 
{
	// return cur_width;
	return 0;
}