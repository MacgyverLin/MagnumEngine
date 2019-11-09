#include "wxdef.h"
#include "fontdialog.h"

FontDialog::FontDialog(const wxString & title)
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(300, 200))
{
	wxPanel *panel = new wxPanel(this, -1);

	wxMenuBar *menubar = new wxMenuBar;
	wxMenu *file = new wxMenu;
	file->Append(ID_FONTDIALOG, wxT("&Change font"));
	menubar->Append(file, wxT("&File"));
	SetMenuBar(menubar);

	Connect(ID_FONTDIALOG, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(FontDialog::OnOpen));

	st = new wxStaticText(panel, wxID_ANY, wxT("The Agoge"), wxPoint(20, 20));

	Center();
}


void FontDialog::OnOpen(wxCommandEvent& WXUNUSED(event))
{
	wxFontDialog *fontDialog = new wxFontDialog(this);

	if (fontDialog->ShowModal() == wxID_OK) 
	{
		st->SetFont(fontDialog->GetFontData().GetChosenFont());
	}
}