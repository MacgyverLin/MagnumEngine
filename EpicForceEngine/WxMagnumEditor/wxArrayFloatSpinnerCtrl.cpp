#include "wxArrayFloatSpinnerCtrl.h"

////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC_CLASS( wxArrayFloatSpinnerCtrlEvent, wxNotifyEvent )
DEFINE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_FLOAT_SPINNER_CTRL_VALUE_CHANGED )
////////////////////////////////////////////////////////////////////////////////////////

wxArrayFloatSpinnerCtrl::wxArrayFloatSpinnerCtrl(wxWindow *parent_, wxWindowID id_,
											     const char *label_,
											     const Vector<float> &values_, float minValue_, float maxValue_,
											     wxWindow *topLevelWindow_,
											     const wxPoint &pos_, const wxSize &size_,
											     long style_)
: wxCollapsePanelCtrl(parent_, id_, label_, topLevelWindow_, pos_, size_, style_)
, values(values_), minValue(minValue_), maxValue(maxValue_)
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
	numElementsSpinner->Connect(wxEVT_COMMAND_ARRAY_LENGTH_CTRL_VALUE_CHANGED, wxArrayLengthCtrlHandler(wxArrayFloatSpinnerCtrl::onLengthChanged)		, 0, this);
	
	createElementsUI();
}

void wxArrayFloatSpinnerCtrl::setLength(int length_)
{
	resizeElementsUI(length_);
}

int wxArrayFloatSpinnerCtrl::getLength() const
{
	return floatSpinners.length();
}

void wxArrayFloatSpinnerCtrl::setMinValue(float minValue_)
{
	minValue = minValue_;

	for(int i=0; i<floatSpinners.length(); i++)
		floatSpinners[i]->setMinValue(minValue_);
}

float wxArrayFloatSpinnerCtrl::getMinValue() const
{
	return minValue;
}

void wxArrayFloatSpinnerCtrl::setMaxValue(float maxValue_)
{
	maxValue = maxValue_;

	for(int i=0; i<floatSpinners.length(); i++)
		floatSpinners[i]->setMaxValue(maxValue);
}

float wxArrayFloatSpinnerCtrl::getMaxValue() const
{
	return maxValue;
}

void wxArrayFloatSpinnerCtrl::setValue(int idx, float value_)
{
	values[idx] = value_;
	floatSpinners[idx]->setValue(value_);
}

float wxArrayFloatSpinnerCtrl::getValue(int idx) const
{
	return floatSpinners[idx]->getValue();
}

void wxArrayFloatSpinnerCtrl::createElementsUI()
{
	wxWindow *contentPanel = this->GetPane();

	floatSpinners.resize(values.length());
	for(int i=0; i<floatSpinners.length(); i++)
	{
		wxString str;
		str.Printf("Element%d", i);
		floatSpinners[i] = new wxFloatSpinnerCtrl(contentPanel, wxID_ANY, str, 
												  values[i], minValue, maxValue, 
												  128, 120,
			                                      wxDefaultPosition, wxDefaultSize);
		flexSizer->Add(floatSpinners[i], 1, wxBOTTOM | wxEXPAND, 4);

		floatSpinners[i]->Connect(wxEVT_COMMAND_FLOAT_SPINNER_CTRL_VALUE_CHANGED, wxFloatSpinnerCtrlEventHandler(wxArrayFloatSpinnerCtrl::onFloatValueChanged)		, 0, this);
	}
}

void wxArrayFloatSpinnerCtrl::destroyElementsUI()
{
	for(int i=0; i<floatSpinners.length(); i++)
	{
		delete floatSpinners[i];
	}
	floatSpinners.destroy();
}

void wxArrayFloatSpinnerCtrl::resizeElementsUI(int newLength)
{
	int oldLength = values.length();
	if(newLength==oldLength)
		return;

	float lastValue = 0;
	if(newLength>oldLength && values.length()!=0)
		lastValue = values.back();

	values.resize(newLength);
	for(int i=oldLength; i<values.length(); i++)
		values[i] = lastValue;

	destroyElementsUI();
	createElementsUI();

	wxArrayFloatSpinnerCtrlEvent event(wxEVT_COMMAND_ARRAY_FLOAT_SPINNER_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(values);
	
	GetEventHandler()->ProcessEvent( event );
}

void wxArrayFloatSpinnerCtrl::onLengthChanged(wxArrayLengthCtrlEvent &evt)
{
	int newLength = evt.GetLength();
	
	resizeElementsUI(newLength);

	this->OnStateChange(this->GetBestSize());
}

void wxArrayFloatSpinnerCtrl::onFloatValueChanged(wxFloatSpinnerCtrlEvent &evt)
{
	int idx = 0;
	for(int i=0; i<floatSpinners.length(); i++)
	{
		if(floatSpinners[i]==evt.GetEventObject())
		{
			idx = i;
			break;
		}
	}

	values[idx] = evt.GetValue();

	wxArrayFloatSpinnerCtrlEvent event(wxEVT_COMMAND_ARRAY_FLOAT_SPINNER_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(values);
	
	GetEventHandler()->ProcessEvent( event );
}