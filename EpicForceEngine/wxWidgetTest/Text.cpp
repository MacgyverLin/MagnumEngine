#include "text.h"

Text::Text(const wxString& title)
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(250, 150))
{
	Connect(wxEVT_PAINT, wxPaintEventHandler(Text::OnPaint));
	Centre();
}

void Text::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);

	dc.DrawText(wxT("Lin Koon Wing"), 40, 60);
	dc.DrawText(wxT("Lin Koon Wing"), 70, 80);
}
