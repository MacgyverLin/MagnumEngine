#include "wxFloatSpinnerCtrl.h"

////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC_CLASS( wxFloatSpinnerCtrlEvent, wxNotifyEvent )
DEFINE_EVENT_TYPE( wxEVT_COMMAND_FLOAT_SPINNER_CTRL_VALUE_CHANGED )

////////////////////////////////////////////////////////////////////////////////////////
wxFloatSpinnerCtrl::wxFloatSpinnerCtrl(wxWindow *parent_, wxWindowID id_,
									   const char *label_,
									   float value_, float minValue_, float maxValue_,
									   int labelWidth_, int textBoxWidth_,
									   const wxPoint &pos_, const wxSize &size_,
									   long style_)
: wxPanel(parent_, id_, pos_, size_, style_)
, value(value_), minValue(minValue_), maxValue(maxValue_)
, residue(0)
, unitPerPixel(0.01)
, dragging(false)
{
	SetForegroundColour(parent_->GetForegroundColour());
    SetBackgroundColour(parent_->GetBackgroundColour());

	staticText = new wxStaticText(this, wxID_ANY, label_       , wxDefaultPosition, wxDefaultSize);
	staticText->SetMinSize(wxSize(labelWidth_, COLLAPSE_BUTTON_SIZE));
    staticText->SetForegroundColour(parent_->GetForegroundColour());
    staticText->SetBackgroundColour(parent_->GetBackgroundColour());
	
	textCtrl   = new wxTextCtrl  (this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_RIGHT | wxTE_PROCESS_ENTER | wxBORDER_SIMPLE);
	textCtrl->SetMinSize(wxSize(textBoxWidth_, COLLAPSE_BUTTON_SIZE));
    //textCtrl->SetForegroundColour(parent_->GetForegroundColour());
    //textCtrl->SetBackgroundColour(parent_->GetBackgroundColour());

	const wxChar *numbers[] = 	{  
									wxT("-"), wxT("+"), wxT("."), 
									wxT("0"), wxT("1"), wxT("2"), wxT("3"), wxT("4"), 
									wxT("5"), wxT("6"), wxT("7"), wxT("8"), wxT("9") 
								}; 
    wxTextValidator vld(wxFILTER_INCLUDE_CHAR_LIST);
	vld.SetIncludes(wxArrayString(13, numbers));
	textCtrl->SetValidator(vld);
	
	wxBoxSizer *hBox = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizer(hBox);
	hBox->Add(staticText, 0);
	hBox->Add(textCtrl  , 1, wxEXPAND);

	staticText->Connect	(wxEVT_LEFT_DOWN			, wxMouseEventHandler	(wxFloatSpinnerCtrl::onMouseDown)				, 0, this);
	staticText->Connect	(wxEVT_LEFT_UP				, wxMouseEventHandler	(wxFloatSpinnerCtrl::onMouseUp)					, 0, this);
	staticText->Connect	(wxEVT_MOTION				, wxMouseEventHandler	(wxFloatSpinnerCtrl::onMove)					, 0, this);
	staticText->Connect (wxEVT_MOUSE_CAPTURE_LOST   , wxMouseCaptureLostEventHandler(wxFloatSpinnerCtrl::onMouseCaptureLost), 0, this);

	textCtrl->Connect	(wxEVT_COMMAND_TEXT_ENTER	, wxCommandEventHandler	(wxFloatSpinnerCtrl::onTextEntered)				, 0, this);

	updateValue(value, 0);
	updateUIValue();
}

void wxFloatSpinnerCtrl::setMinValue(float minValue_)
{
	minValue		= minValue_;
}

float wxFloatSpinnerCtrl::getMinValue() const
{
	return minValue;
}

void wxFloatSpinnerCtrl::setMaxValue(float maxValue_)
{
	maxValue	= maxValue_;
}

float wxFloatSpinnerCtrl::getMaxValue() const
{
	return maxValue;
}

void wxFloatSpinnerCtrl::setValue(float value_)
{
	updateValue(value_, 0);
	updateUIValue();
}

float wxFloatSpinnerCtrl::getValue() const
{
	return value;
}

void wxFloatSpinnerCtrl::calculateUnitPerPixel()
{
	float screenHeight	= wxSystemSettings::GetMetric(wxSYS_SCREEN_Y);
	unitPerPixel		= fabs((float)value) * 9 / (screenHeight-2);
	if(unitPerPixel<0.01)
		unitPerPixel = 0.01;
}

float wxFloatSpinnerCtrl::updateMouse()
{
	wxPoint position	= wxGetMousePosition();
	float screenHeight	= wxSystemSettings::GetMetric(wxSYS_SCREEN_Y);
	float delta			= 0.0f;

	if(position.y>screenHeight-2)
	{
		wxPoint newScreenPosition = wxPoint(position.x, 1);
		
		wxPoint newClientPos	  = ScreenToClient(newScreenPosition);

		WarpPointer(newClientPos.x, newClientPos.y);

		oldPosition = newScreenPosition;
	}
	else if(position.y<1)
	{
		wxPoint newScreenPosition = wxPoint(position.x, screenHeight-2);
		
		wxPoint newClientPos	  = ScreenToClient(newScreenPosition);

		WarpPointer(newClientPos.x, newClientPos.y);

		oldPosition = newScreenPosition;
	}
	else
	{
		wxPoint dpos = position - oldPosition;
		float length = dpos.y;
		if(length>10000)
			length=10000;
		else if(length<-10000)
			length=-10000;
		delta = -length * unitPerPixel;

		oldPosition = position;
	}

	return delta;
}

float wxFloatSpinnerCtrl::getIncrement(float delta)
{
	residue = 0;

	return delta;
}

void wxFloatSpinnerCtrl::updateValue(float oldvalue, float delta)
{
	float newValue = oldvalue;
	newValue += delta;

	if(newValue > maxValue)
		value = maxValue;
	else if(newValue < minValue)
		value = minValue;
	else
		value = newValue;
}

void wxFloatSpinnerCtrl::updateUIValue()
{
	textCtrl->SetValue(getValueText());
}

wxString wxFloatSpinnerCtrl::getValueText()
{
	wxString text;

	text.Printf("%.3f", value);

	return text;
}

void wxFloatSpinnerCtrl::fireEvent()
{
	wxFloatSpinnerCtrlEvent event(wxEVT_COMMAND_FLOAT_SPINNER_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(value);

	GetEventHandler()->ProcessEvent( event );
}

void wxFloatSpinnerCtrl::onMouseDown(wxMouseEvent &evt)
{
	if(!dragging)
	{
		mouseDownPosition	= wxGetMousePosition();
		oldPosition			= wxGetMousePosition();

		calculateUnitPerPixel();
		
		float delta = getIncrement(updateMouse());
		updateValue(value, delta);
		updateUIValue();

		dragging = true;

		if(!staticText->HasCapture())
			staticText->CaptureMouse();
		
		Refresh();
	}
}

void wxFloatSpinnerCtrl::onMouseUp(wxMouseEvent &evt)
{
	if(dragging)
	{
		float delta = getIncrement(updateMouse());
		updateValue(value, delta);
		updateUIValue();

		dragging = false;

		if(staticText->HasCapture())
			staticText->ReleaseMouse();

		Refresh();
		
		fireEvent();
	}
}

void wxFloatSpinnerCtrl::onMove(wxMouseEvent &evt)
{
	if(dragging)
	{
		float delta = getIncrement(updateMouse());
		updateValue(value, delta);
		updateUIValue();

		fireEvent();

		Refresh();
	}
}

void wxFloatSpinnerCtrl::onMouseCaptureLost(wxMouseCaptureLostEvent& evt)
{
	if(staticText->HasCapture())
		staticText->ReleaseMouse();
}

void wxFloatSpinnerCtrl::onTextEntered(wxCommandEvent &evt)
{
	float newValue = atof(textCtrl->GetValue().c_str());
	updateValue(newValue, 0);
	updateUIValue();

	Refresh();

	fireEvent();
}