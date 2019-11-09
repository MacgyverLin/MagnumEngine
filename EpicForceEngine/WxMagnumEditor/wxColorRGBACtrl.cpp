#include "wxColorRGBACtrl.h"
#include "wxColorDlg.h"

////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC_CLASS( wxColorRGBACtrlEvent, wxNotifyEvent )
DEFINE_EVENT_TYPE( wxEVT_COMMAND_COLORRGBA_CTRL_VALUE_CHANGED )

////////////////////////////////////////////////////////////////////////////////////////
wxColorRGBACtrl::wxColorRGBACtrl(wxWindow *parent_, wxWindowID id_,
								 const char *label_, const ColorRGBA &value_, 
								 const wxPoint &pos_, const wxSize &size_,
								 long style_)
: wxPanel(parent_, id_, pos_, size_, style_)
, value(value_)
{
	SetForegroundColour(parent_->GetForegroundColour());
    SetBackgroundColour(parent_->GetBackgroundColour());

	staticText = new wxStaticText(this, wxID_ANY, label_, wxDefaultPosition, wxDefaultSize);
    staticText->SetForegroundColour(parent_->GetForegroundColour());
    staticText->SetBackgroundColour(parent_->GetBackgroundColour());
	staticText->SetMinSize(wxSize(128, COLLAPSE_BUTTON_SIZE*1.5));

	colorSwatch = new wxStaticText(this, wxID_ANY, ""   , wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
	colorSwatch->SetMinSize(wxSize(120, COLLAPSE_BUTTON_SIZE*1.5));
	setValue(value_);

	wxBoxSizer *hBox = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizer(hBox);
	hBox->Add(staticText , 0);
	hBox->Add(colorSwatch, 1, wxEXPAND);
		
	colorSwatch->Connect(wxEVT_LEFT_DOWN			, wxMouseEventHandler(wxColorRGBACtrl::OnMouseDown)		, 0, this);
	colorSwatch->Connect(wxEVT_PAINT				, wxPaintEventHandler(wxColorRGBACtrl::OnPaint)			, 0, this);
}

void wxColorRGBACtrl::setValue(const ColorRGBA &value_)
{
	value = value_;

	wxColor col(value.R()*255, value.G()*255, value.B()*255, value.A()*255);
	colorSwatch->SetForegroundColour(col);
    colorSwatch->SetBackgroundColour(col);

	Refresh();
}

ColorRGBA wxColorRGBACtrl::getValue() const
{
	return value;
}

void wxColorRGBACtrl::fireEvent()
{
	wxColorRGBACtrlEvent event(wxEVT_COMMAND_COLORRGBA_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(value);
	
	GetEventHandler()->ProcessEvent( event );
}

void wxColorRGBACtrl::OnMouseDown(wxMouseEvent &evt)
{
	wxColourDialog colorDlg(this);
	colorDlg.GetColourData().GetColour() = colorSwatch->GetBackgroundColour();

	if(colorDlg.ShowModal() == wxID_OK) 
	{
		wxColor newColor = colorDlg.GetColourData().GetColour();

		float r = ((float)(newColor.Red()  )) / 255.0f;
		float g = ((float)(newColor.Green())) / 255.0f;
		float b = ((float)(newColor.Blue() )) / 255.0f;
		float a = value.A();

		ColorRGBA col(r, g, b, a);
		setValue(col);

		Refresh();

		fireEvent();
	}
}

void wxColorRGBACtrl::OnPaint(wxPaintEvent& event)
{
	wxFont font(9, 
				wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
				wxFONTWEIGHT_NORMAL, false, 
				wxT("Courier 10 Pitch"));

	wxPaintDC dc(colorSwatch);
	dc.SetFont(font);

	wxColor bgColor = colorSwatch->GetBackgroundColour();

	wxSize size = colorSwatch->GetSize();
	int colorSwatchHeight = size.y*0.7;
	int alphaSwatchHeight = size.y*0.3;
	int alphaSwatchWidth  = size.x * bgColor.Alpha() / 255;

	dc.SetPen(wxPen(bgColor)); 
	dc.SetBrush(wxBrush(bgColor));
	dc.DrawRectangle(0, 0, size.x, colorSwatchHeight);

	dc.SetPen(wxPen(wxColor(0, 0, 0))); 
	dc.SetBrush(wxBrush(wxColor(0, 0, 0)));
	dc.DrawRectangle(0, 0+colorSwatchHeight, size.x, alphaSwatchHeight);

	dc.SetPen(wxPen(wxColor(255, 255, 255))); 
	dc.SetBrush(wxBrush(wxColor(255, 255, 255)));
	dc.DrawRectangle(0, 0+colorSwatchHeight, alphaSwatchWidth, alphaSwatchHeight);

	dc.SetPen(wxPen(wxColor(0, 0, 0))); 
	dc.SetBrush(wxBrush(wxColor(0, 0, 0)));
	dc.DrawLine(0, 0+colorSwatchHeight, size.x, 0+colorSwatchHeight);
}