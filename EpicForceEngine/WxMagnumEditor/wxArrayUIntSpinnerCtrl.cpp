#include "wxArrayUIntSpinnerCtrl.h"

////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC_CLASS( wxArrayUIntSpinnerCtrlEvent, wxNotifyEvent )
DEFINE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_UINT_SPINNER_CTRL_VALUE_CHANGED )
////////////////////////////////////////////////////////////////////////////////////////

wxArrayUIntSpinnerCtrl::wxArrayUIntSpinnerCtrl(wxWindow *parent_, wxWindowID id_,
											  const char *label_,
											  const Vector<unsigned int> &values_, unsigned int minValue_, unsigned int maxValue_,
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
	numElementsSpinner->Connect(wxEVT_COMMAND_ARRAY_LENGTH_CTRL_VALUE_CHANGED, wxArrayLengthCtrlHandler(wxArrayUIntSpinnerCtrl::onLengthChanged)		, 0, this);
	
	createElementsUI();
}

void wxArrayUIntSpinnerCtrl::setLength(int length_)
{
	resizeElementsUI(length_);
}

int wxArrayUIntSpinnerCtrl::getLength() const
{
	return uintSpinners.length();
}

void wxArrayUIntSpinnerCtrl::setMinValue(unsigned int minValue_)
{
	minValue = minValue_;

	for(int i=0; i<uintSpinners.length(); i++)
		uintSpinners[i]->setMinValue(minValue_);
}

unsigned int wxArrayUIntSpinnerCtrl::getMinValue() const
{
	return minValue;
}

void wxArrayUIntSpinnerCtrl::setMaxValue(unsigned int maxValue_)
{
	maxValue = maxValue_;

	for(int i=0; i<uintSpinners.length(); i++)
		uintSpinners[i]->setMaxValue(maxValue);
}

unsigned int wxArrayUIntSpinnerCtrl::getMaxValue() const
{
	return maxValue;
}

void wxArrayUIntSpinnerCtrl::setValue(int idx, unsigned int value_)
{
	values[idx] = value_;
	uintSpinners[idx]->setValue(value_);
}

unsigned int wxArrayUIntSpinnerCtrl::getValue(int idx) const
{
	return uintSpinners[idx]->getValue();
}

void wxArrayUIntSpinnerCtrl::createElementsUI()
{
	wxWindow *contentPanel = this->GetPane();

	uintSpinners.resize(values.length());
	for(int i=0; i<uintSpinners.length(); i++)
	{
		wxString str;
		str.Printf("Element%d", i);
		uintSpinners[i] = new wxUIntSpinnerCtrl(contentPanel, wxID_ANY, str, 
											    values[i], minValue, maxValue, 
											    128, 120,
			                                    wxDefaultPosition, wxDefaultSize);
		flexSizer->Add(uintSpinners[i], 1, wxBOTTOM | wxEXPAND, 4);

		uintSpinners[i]->Connect(wxEVT_COMMAND_UINT_SPINNER_CTRL_VALUE_CHANGED, wxUIntSpinnerCtrlEventHandler(wxArrayUIntSpinnerCtrl::onUIntValueChanged)		, 0, this);
	}
}

void wxArrayUIntSpinnerCtrl::destroyElementsUI()
{
	for(int i=0; i<uintSpinners.length(); i++)
	{
		delete uintSpinners[i];
	}
	uintSpinners.destroy();
}

void wxArrayUIntSpinnerCtrl::resizeElementsUI(int newLength)
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

	wxArrayUIntSpinnerCtrlEvent event(wxEVT_COMMAND_ARRAY_UINT_SPINNER_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(values);
	
	GetEventHandler()->ProcessEvent( event );
}

void wxArrayUIntSpinnerCtrl::onLengthChanged(wxArrayLengthCtrlEvent &evt)
{
	int newLength = evt.GetLength();
	
	resizeElementsUI(newLength);

	this->OnStateChange(this->GetBestSize());
}

void wxArrayUIntSpinnerCtrl::onUIntValueChanged(wxUIntSpinnerCtrlEvent &evt)
{
	int idx = 0;
	for(int i=0; i<uintSpinners.length(); i++)
	{
		if(uintSpinners[i]==evt.GetEventObject())
		{
			idx = i;
			break;
		}
	}

	values[idx] = evt.GetValue();

	wxArrayUIntSpinnerCtrlEvent event(wxEVT_COMMAND_ARRAY_UINT_SPINNER_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(values);
	
	GetEventHandler()->ProcessEvent( event );
}