#include "Widget.h"
#include "Burning.h"

int num[] = { 75, 150, 225, 300, 375, 450, 525, 600, 675 };
int asize = sizeof(num)/sizeof(num[1]);

Widget::Widget(wxPanel *parent, int id)
: wxPanel(parent, id, wxDefaultPosition, wxSize(-1, 30), wxSUNKEN_BORDER)
{
	m_parent = parent;

	Connect(wxEVT_PAINT, wxPaintEventHandler(Widget::OnPaint));
	Connect(wxEVT_SIZE , wxSizeEventHandler(Widget::OnSize));
}

void Widget::OnPaint(wxPaintEvent& event)
{
	wxFont font(9, 
				wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
				wxFONTWEIGHT_NORMAL, false, 
				wxT("Courier 10 Pitch"));

	wxPaintDC dc(this);
	dc.SetFont(font);
	wxSize size = GetSize();
	int width = size.GetWidth();

	Burning *burn = (Burning *)m_parent->GetParent();

	int cur_width = burn->GetCurWidth();

	int step = (int) ceil(width / 10.0);
	int till = (int) ((width / 750.0) * cur_width);
	int full = (int) ((width / 750.0) * 700);

	if(cur_width >= 700)
	{
		dc.SetPen(wxPen(wxColour(255, 255, 184))); 
		dc.SetBrush(wxBrush(wxColour(255, 255, 184)));
		dc.DrawRectangle(0, 0, full, 30);
		dc.SetPen(wxPen(wxColour(255, 175, 175)));
		dc.SetBrush(wxBrush(wxColour(255, 175, 175)));
		dc.DrawRectangle(full, 0, till-full, 30);
	} 
	else 
	{ 
		dc.SetPen(wxPen(wxColour(255, 255, 184)));
		dc.SetBrush(wxBrush(wxColour(255, 255, 184)));
		dc.DrawRectangle(0, 0, till, 30);
	}

	dc.SetPen(wxPen(wxColour(90, 80, 60)));
	for(int i=1; i<=asize; i++)
	{
		dc.DrawLine(i*step, 0, i*step, 6);
		wxSize size = dc.GetTextExtent(wxString::Format(wxT("%d"), num[i-1]));
		dc.DrawText(wxString::Format(wxT("%d"), num[i-1]), 
			i*step-size.GetWidth()/2, 8);
	}
}

void Widget::OnSize(wxSizeEvent& event)
{
	Refresh();
}