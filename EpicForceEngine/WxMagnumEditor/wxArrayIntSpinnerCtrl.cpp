#include "wxArrayIntSpinnerCtrl.h"

////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC_CLASS( wxArrayIntSpinnerCtrlEvent, wxNotifyEvent )
DEFINE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_INT_SPINNER_CTRL_VALUE_CHANGED )
////////////////////////////////////////////////////////////////////////////////////////

wxArrayIntSpinnerCtrl::wxArrayIntSpinnerCtrl(wxWindow *parent_, wxWindowID id_,
											 const char *label_,
											 const Vector<int> &values_, int minValue_, int maxValue_,
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
	numElementsSpinner->Connect(wxEVT_COMMAND_ARRAY_LENGTH_CTRL_VALUE_CHANGED, wxArrayLengthCtrlHandler(wxArrayIntSpinnerCtrl::onLengthChanged)		, 0, this);
	
	createElementsUI();
}

void wxArrayIntSpinnerCtrl::setLength(int length_)
{
	resizeElementsUI(length_);
}

int wxArrayIntSpinnerCtrl::getLength() const
{
	return intSpinners.length();
}

void wxArrayIntSpinnerCtrl::setMinValue(int minValue_)
{
	minValue = minValue_;

	for(int i=0; i<intSpinners.length(); i++)
		intSpinners[i]->setMinValue(minValue_);
}

int wxArrayIntSpinnerCtrl::getMinValue() const
{
	return minValue;
}

void wxArrayIntSpinnerCtrl::setMaxValue(int maxValue_)
{
	maxValue = maxValue_;

	for(int i=0; i<intSpinners.length(); i++)
		intSpinners[i]->setMaxValue(maxValue);
}

int wxArrayIntSpinnerCtrl::getMaxValue() const
{
	return maxValue;
}

void wxArrayIntSpinnerCtrl::setValue(int idx, int value_)
{
	values[idx] = value_;
	intSpinners[idx]->setValue(value_);
}

int wxArrayIntSpinnerCtrl::getValue(int idx) const
{
	return intSpinners[idx]->getValue();
}

void wxArrayIntSpinnerCtrl::createElementsUI()
{
	wxWindow *contentPanel = this->GetPane();

	intSpinners.resize(values.length());
	for(int i=0; i<intSpinners.length(); i++)
	{
		wxString str;
		str.Printf("Element%d", i);
		intSpinners[i] = new wxIntSpinnerCtrl(contentPanel, wxID_ANY, str, 
											  values[i], minValue, maxValue, 
											  128, 120,
			                                  wxDefaultPosition, wxDefaultSize);
		flexSizer->Add(intSpinners[i], 1, wxBOTTOM | wxEXPAND, 4);

		intSpinners[i]->Connect(wxEVT_COMMAND_INT_SPINNER_CTRL_VALUE_CHANGED, wxIntSpinnerCtrlEventHandler(wxArrayIntSpinnerCtrl::onIntValueChanged)		, 0, this);
	}
}

void wxArrayIntSpinnerCtrl::destroyElementsUI()
{
	for(int i=0; i<intSpinners.length(); i++)
	{
		delete intSpinners[i];
	}
	intSpinners.destroy();
}

void wxArrayIntSpinnerCtrl::resizeElementsUI(int newLength)
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

	wxArrayIntSpinnerCtrlEvent event(wxEVT_COMMAND_ARRAY_INT_SPINNER_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(values);
	
	GetEventHandler()->ProcessEvent( event );
}

void wxArrayIntSpinnerCtrl::onLengthChanged(wxArrayLengthCtrlEvent &evt)
{
	int newLength = evt.GetLength();
	
	resizeElementsUI(newLength);

	this->OnStateChange(this->GetBestSize());
}

void wxArrayIntSpinnerCtrl::onIntValueChanged(wxIntSpinnerCtrlEvent &evt)
{
	int idx = 0;
	for(int i=0; i<intSpinners.length(); i++)
	{
		if(intSpinners[i]==evt.GetEventObject())
		{
			idx = i;
			break;
		}
	}

	values[idx] = evt.GetValue();

	wxArrayIntSpinnerCtrlEvent event(wxEVT_COMMAND_ARRAY_INT_SPINNER_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(values);
	
	GetEventHandler()->ProcessEvent( event );
}