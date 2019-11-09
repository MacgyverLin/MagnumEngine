#include "wxArrayColorRGBACtrl.h"

////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC_CLASS( wxArrayColorRGBACtrlEvent, wxNotifyEvent )
DEFINE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_COLORRGBA_CTRL_VALUE_CHANGED )
////////////////////////////////////////////////////////////////////////////////////////

wxArrayColorRGBACtrl::wxArrayColorRGBACtrl(wxWindow *parent_, wxWindowID id_,
									       const char *label_,
										   const Vector<ColorRGBA> &values_, 
										   wxWindow *topLevelWindow_,
										   const wxPoint &pos_, const wxSize &size_,
										   long style_)
: wxCollapsePanelCtrl(parent_, id_, label_, topLevelWindow_, pos_, size_, style_)
, values(values_)
{
	wxWindow *contentPanel = this->GetPane();

	hBox		= new wxBoxSizer(wxHORIZONTAL);
	flexSizer	= new wxFlexGridSizer(1); flexSizer->AddGrowableCol(0);
	contentPanel->SetSizer(hBox);
		hBox->Add(COLLAPSE_BUTTON_SIZE*1.5, COLLAPSE_BUTTON_SIZE, 0);
		hBox->Add(flexSizer, 1, wxEXPAND);

	numElementsSpinner = new wxArrayLengthCtrl(contentPanel, wxID_ANY, "Length", values.length(), 
											   wxDefaultPosition, wxDefaultSize);
	flexSizer->Add(numElementsSpinner, 1, wxBOTTOM | wxEXPAND, 4);
	numElementsSpinner->Connect(wxEVT_COMMAND_ARRAY_LENGTH_CTRL_VALUE_CHANGED, wxArrayLengthCtrlHandler(wxArrayColorRGBACtrl::onLengthChanged)		, 0, this);
	
	createElementsUI();
}

void wxArrayColorRGBACtrl::setLength(int length_)
{
	resizeElementsUI(length_);
}

int wxArrayColorRGBACtrl::getLength() const
{
	return colorRGBACtrls.length();
}

void wxArrayColorRGBACtrl::setValue(int idx, const ColorRGBA &value_)
{
	values[idx] = value_;
	colorRGBACtrls[idx]->setValue(value_);
}

ColorRGBA wxArrayColorRGBACtrl::getValue(int idx) const
{
	return colorRGBACtrls[idx]->getValue();
}

void wxArrayColorRGBACtrl::createElementsUI()
{
	wxWindow *contentPanel = this->GetPane();

	colorRGBACtrls.resize(values.length());
	for(int i=0; i<colorRGBACtrls.length(); i++)
	{
		wxString str;
		str.Printf("Element%d", i);
		colorRGBACtrls[i] = new wxColorRGBACtrl(contentPanel, wxID_ANY, 
			                                    str, 
												values[i], 
			                                    wxDefaultPosition, wxDefaultSize);
		flexSizer->Add(colorRGBACtrls[i], 1, wxBOTTOM | wxEXPAND, 4);

		colorRGBACtrls[i]->Connect(wxEVT_COMMAND_COLORRGBA_CTRL_VALUE_CHANGED, wxColorRGBACtrlEventHandler(wxArrayColorRGBACtrl::onColorRGBAValueChanged)		, 0, this);
	}
}

void wxArrayColorRGBACtrl::destroyElementsUI()
{
	for(int i=0; i<colorRGBACtrls.length(); i++)
	{
		delete colorRGBACtrls[i];
	}
	colorRGBACtrls.destroy();
}

void wxArrayColorRGBACtrl::resizeElementsUI(int newLength)
{
	int oldLength = values.length();
	if(newLength==oldLength)
		return;

	ColorRGBA lastValue(128, 128, 128, 255);
	if(newLength>oldLength && values.length()!=0)
		lastValue = values.back();

	values.resize(newLength);
	for(int i=oldLength; i<values.length(); i++)
		values[i] = lastValue;

	destroyElementsUI();
	createElementsUI();

	wxArrayColorRGBACtrlEvent event(wxEVT_COMMAND_ARRAY_COLORRGBA_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(values);
	
	GetEventHandler()->ProcessEvent( event );
}

void wxArrayColorRGBACtrl::onLengthChanged(wxArrayLengthCtrlEvent &evt)
{
	int newLength = evt.GetLength();
	
	resizeElementsUI(newLength);

	this->OnStateChange(this->GetBestSize());
}

void wxArrayColorRGBACtrl::onColorRGBAValueChanged(wxColorRGBACtrlEvent &evt)
{
	int idx = 0;
	for(int i=0; i<colorRGBACtrls.length(); i++)
	{
		if(colorRGBACtrls[i]==evt.GetEventObject())
		{
			idx = i;
			break;
		}
	}

	values[idx] = evt.GetValue();

	wxArrayColorRGBACtrlEvent event(wxEVT_COMMAND_ARRAY_COLORRGBA_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(values);
	
	GetEventHandler()->ProcessEvent( event );
}