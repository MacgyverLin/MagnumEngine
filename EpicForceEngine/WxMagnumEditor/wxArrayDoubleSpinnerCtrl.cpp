#include "wxArrayDoubleSpinnerCtrl.h"

////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC_CLASS( wxArrayDoubleSpinnerCtrlEvent, wxNotifyEvent )
DEFINE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_DOUBLE_SPINNER_CTRL_VALUE_CHANGED )
////////////////////////////////////////////////////////////////////////////////////////

wxArrayDoubleSpinnerCtrl::wxArrayDoubleSpinnerCtrl(wxWindow *parent_, wxWindowID id_,
												   const char *label_,
												   const Vector<double> &values_, const double &minValue_, const double &maxValue_,
												   wxWindow *topLevelWindow_,
												   const wxPoint &pos_, const wxSize &size_,
												   long style_)
: wxCollapsePanelCtrl(parent_, id_, label_, topLevelWindow_, pos_, size_, style_)
, minValue(minValue_)
, maxValue(maxValue_)
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
	numElementsSpinner->Connect(wxEVT_COMMAND_ARRAY_LENGTH_CTRL_VALUE_CHANGED, wxArrayLengthCtrlHandler(wxArrayDoubleSpinnerCtrl::onLengthChanged)		, 0, this);
	
	createElementsUI();
}

void wxArrayDoubleSpinnerCtrl::setLength(int length_)
{
	resizeElementsUI(length_);
}

int wxArrayDoubleSpinnerCtrl::getLength() const
{
	return doubleSpinners.length();
}

void wxArrayDoubleSpinnerCtrl::setMinValue(const double &minValue_)
{
	minValue = minValue_;

	for(int i=0; i<doubleSpinners.length(); i++)
		doubleSpinners[i]->setMinValue(minValue_);
}

double wxArrayDoubleSpinnerCtrl::getMinValue() const
{
	return minValue;
}

void wxArrayDoubleSpinnerCtrl::setMaxValue(const double &maxValue_)
{
	maxValue = maxValue_;

	for(int i=0; i<doubleSpinners.length(); i++)
		doubleSpinners[i]->setMaxValue(maxValue);
}

double wxArrayDoubleSpinnerCtrl::getMaxValue() const
{
	return maxValue;
}

void wxArrayDoubleSpinnerCtrl::setValue(int idx, const double &value_)
{
	values[idx] = value_;
	doubleSpinners[idx]->setValue(value_);
}

double wxArrayDoubleSpinnerCtrl::getValue(int idx) const
{
	return doubleSpinners[idx]->getValue();
}

void wxArrayDoubleSpinnerCtrl::createElementsUI()
{
	wxWindow *contentPanel = this->GetPane();

	doubleSpinners.resize(values.length());
	for(int i=0; i<doubleSpinners.length(); i++)
	{
		wxString str;
		str.Printf("Element%d", i);
		doubleSpinners[i] = new wxDoubleSpinnerCtrl(contentPanel, wxID_ANY, 
			                                        str, values[i], minValue, maxValue, 
													128, 120,
			                                        wxDefaultPosition, wxDefaultSize);
		flexSizer->Add(doubleSpinners[i], 1, wxBOTTOM | wxEXPAND, 4);

		doubleSpinners[i]->Connect(wxEVT_COMMAND_DOUBLE_SPINNER_CTRL_VALUE_CHANGED, wxDoubleSpinnerCtrlEventHandler(wxArrayDoubleSpinnerCtrl::onDoubleValueChanged)		, 0, this);
	}
}

void wxArrayDoubleSpinnerCtrl::destroyElementsUI()
{
	for(int i=0; i<doubleSpinners.length(); i++)
	{
		delete doubleSpinners[i];
	}
	doubleSpinners.destroy();
}

void wxArrayDoubleSpinnerCtrl::resizeElementsUI(int newLength)
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

	wxArrayDoubleSpinnerCtrlEvent event(wxEVT_COMMAND_ARRAY_DOUBLE_SPINNER_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(values);
	
	GetEventHandler()->ProcessEvent( event );
}

void wxArrayDoubleSpinnerCtrl::onLengthChanged(wxArrayLengthCtrlEvent &evt)
{
	int newLength = evt.GetLength();
	
	resizeElementsUI(newLength);

	this->OnStateChange(this->GetBestSize());
}

void wxArrayDoubleSpinnerCtrl::onDoubleValueChanged(wxDoubleSpinnerCtrlEvent &evt)
{
	int idx = 0;
	for(int i=0; i<doubleSpinners.length(); i++)
	{
		if(doubleSpinners[i]==evt.GetEventObject())
		{
			idx = i;
			break;
		}
	}

	values[idx] = evt.GetValue();

	wxArrayDoubleSpinnerCtrlEvent event(wxEVT_COMMAND_ARRAY_DOUBLE_SPINNER_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(values);
	
	GetEventHandler()->ProcessEvent( event );
}