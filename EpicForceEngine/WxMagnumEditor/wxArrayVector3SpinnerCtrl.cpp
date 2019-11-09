#include "wxArrayVector3SpinnerCtrl.h"

////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC_CLASS( wxArrayVector3SpinnerCtrlEvent, wxNotifyEvent )
DEFINE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_VECTOR3_SPINNER_CTRL_VALUE_CHANGED )
////////////////////////////////////////////////////////////////////////////////////////

wxArrayVector3SpinnerCtrl::wxArrayVector3SpinnerCtrl(wxWindow *parent_, wxWindowID id_,
												     const char *label_,
												     const Vector<Vector3> &values_, const Vector3 &minValue_, const Vector3 &maxValue_,
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
	numElementsSpinner->Connect(wxEVT_COMMAND_ARRAY_LENGTH_CTRL_VALUE_CHANGED, wxArrayLengthCtrlHandler(wxArrayVector3SpinnerCtrl::onLengthChanged)		, 0, this);
	
	createElementsUI();
}

void wxArrayVector3SpinnerCtrl::setLength(int length_)
{
	resizeElementsUI(length_);
}

int wxArrayVector3SpinnerCtrl::getLength() const
{
	return vector3Spinners.length();
}

void wxArrayVector3SpinnerCtrl::setMinValue(const Vector3 &minValue_)
{
	minValue = minValue_;

	for(int i=0; i<vector3Spinners.length(); i++)
		vector3Spinners[i]->setMinValue(minValue_);
}

Vector3 wxArrayVector3SpinnerCtrl::getMinValue() const
{
	return minValue;
}

void wxArrayVector3SpinnerCtrl::setMaxValue(const Vector3 &maxValue_)
{
	maxValue = maxValue_;

	for(int i=0; i<vector3Spinners.length(); i++)
		vector3Spinners[i]->setMaxValue(maxValue);
}

Vector3 wxArrayVector3SpinnerCtrl::getMaxValue() const
{
	return maxValue;
}

void wxArrayVector3SpinnerCtrl::setValue(int idx, const Vector3 &value_)
{
	values[idx] = value_;
	vector3Spinners[idx]->setValue(value_);
}

Vector3 wxArrayVector3SpinnerCtrl::getValue(int idx) const
{
	return vector3Spinners[idx]->getValue();
}

void wxArrayVector3SpinnerCtrl::createElementsUI()
{
	wxWindow *contentPanel = this->GetPane();

	vector3Spinners.resize(values.length());
	for(int i=0; i<vector3Spinners.length(); i++)
	{
		wxString str;
		str.Printf("Element%d", i);
		vector3Spinners[i] = new wxVector3SpinnerCtrl(contentPanel, wxID_ANY, 
			                                          str, true,
													  values[i], minValue, maxValue, 
													  this->GetTopLevelWindow(),
			                                          wxDefaultPosition, wxDefaultSize);
		flexSizer->Add(vector3Spinners[i], 1, wxBOTTOM | wxEXPAND, 4);

		vector3Spinners[i]->Connect(wxEVT_COMMAND_VECTOR3_SPINNER_CTRL_VALUE_CHANGED, wxVector3SpinnerCtrlEventHandler(wxArrayVector3SpinnerCtrl::onVector3ValueChanged)		, 0, this);
	}
}

void wxArrayVector3SpinnerCtrl::destroyElementsUI()
{
	for(int i=0; i<vector3Spinners.length(); i++)
	{
		delete vector3Spinners[i];
	}
	vector3Spinners.destroy();
}

void wxArrayVector3SpinnerCtrl::resizeElementsUI(int newLength)
{
	int oldLength = values.length();
	if(newLength==oldLength)
		return;

	Vector3 lastValue(Vector3::ZERO);
	if(newLength>oldLength && values.length()!=0)
		lastValue = values.back();

	values.resize(newLength);
	for(int i=oldLength; i<values.length(); i++)
		values[i] = lastValue;

	destroyElementsUI();
	createElementsUI();

	wxArrayVector3SpinnerCtrlEvent event(wxEVT_COMMAND_ARRAY_VECTOR3_SPINNER_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(values);
	
	GetEventHandler()->ProcessEvent( event );
}

void wxArrayVector3SpinnerCtrl::onLengthChanged(wxArrayLengthCtrlEvent &evt)
{
	int newLength = evt.GetLength();
	
	resizeElementsUI(newLength);

	this->OnStateChange(this->GetBestSize());
}

void wxArrayVector3SpinnerCtrl::onVector3ValueChanged(wxVector3SpinnerCtrlEvent &evt)
{
	int idx = 0;
	for(int i=0; i<vector3Spinners.length(); i++)
	{
		if(vector3Spinners[i]==evt.GetEventObject())
		{
			idx = i;
			break;
		}
	}

	values[idx] = evt.GetValue();

	wxArrayVector3SpinnerCtrlEvent event(wxEVT_COMMAND_ARRAY_VECTOR3_SPINNER_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(values);
	
	GetEventHandler()->ProcessEvent( evt );
}