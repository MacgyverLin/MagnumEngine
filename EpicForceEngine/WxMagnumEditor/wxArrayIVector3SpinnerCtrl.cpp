#include "wxArrayIVector3SpinnerCtrl.h"

////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC_CLASS( wxArrayIVector3SpinnerCtrlEvent, wxNotifyEvent )
DEFINE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_IVECTOR3_SPINNER_CTRL_VALUE_CHANGED )
////////////////////////////////////////////////////////////////////////////////////////

wxArrayIVector3SpinnerCtrl::wxArrayIVector3SpinnerCtrl(wxWindow *parent_, wxWindowID id_,
												       const char *label_,
												       const Vector<IVector3> &values_, const IVector3 &minValue_, const IVector3 &maxValue_,
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
	numElementsSpinner->Connect(wxEVT_COMMAND_ARRAY_LENGTH_CTRL_VALUE_CHANGED, wxArrayLengthCtrlHandler(wxArrayIVector3SpinnerCtrl::onLengthChanged)		, 0, this);
	
	createElementsUI();
}

void wxArrayIVector3SpinnerCtrl::setLength(int length_)
{
	resizeElementsUI(length_);
}

int wxArrayIVector3SpinnerCtrl::getLength() const
{
	return vector3Spinners.length();
}

void wxArrayIVector3SpinnerCtrl::setMinValue(const IVector3 &minValue_)
{
	minValue = minValue_;

	for(int i=0; i<vector3Spinners.length(); i++)
		vector3Spinners[i]->setMinValue(minValue_);
}

IVector3 wxArrayIVector3SpinnerCtrl::getMinValue() const
{
	return minValue;
}

void wxArrayIVector3SpinnerCtrl::setMaxValue(const IVector3 &maxValue_)
{
	maxValue = maxValue_;

	for(int i=0; i<vector3Spinners.length(); i++)
		vector3Spinners[i]->setMaxValue(maxValue);
}

IVector3 wxArrayIVector3SpinnerCtrl::getMaxValue() const
{
	return maxValue;
}

void wxArrayIVector3SpinnerCtrl::setValue(int idx, const IVector3 &value_)
{
	values[idx] = value_;
	vector3Spinners[idx]->setValue(value_);
}

IVector3 wxArrayIVector3SpinnerCtrl::getValue(int idx) const
{
	return vector3Spinners[idx]->getValue();
}

void wxArrayIVector3SpinnerCtrl::createElementsUI()
{
	wxWindow *contentPanel = this->GetPane();

	vector3Spinners.resize(values.length());
	for(int i=0; i<vector3Spinners.length(); i++)
	{
		wxString str;
		str.Printf("Element%d", i);
		vector3Spinners[i] = new wxIVector3SpinnerCtrl(contentPanel, wxID_ANY, 
			                                           str, true,
													   values[i], minValue, maxValue, 
													   this->GetTopLevelWindow(),
			                                           wxDefaultPosition, wxDefaultSize);
		flexSizer->Add(vector3Spinners[i], 1, wxBOTTOM | wxEXPAND, 4);

		vector3Spinners[i]->Connect(wxEVT_COMMAND_IVECTOR3_SPINNER_CTRL_VALUE_CHANGED, wxIVector3SpinnerCtrlEventHandler(wxArrayIVector3SpinnerCtrl::onIVector3ValueChanged)		, 0, this);
	}
}

void wxArrayIVector3SpinnerCtrl::destroyElementsUI()
{
	for(int i=0; i<vector3Spinners.length(); i++)
	{
		delete vector3Spinners[i];
	}
	vector3Spinners.destroy();
}

void wxArrayIVector3SpinnerCtrl::resizeElementsUI(int newLength)
{
	int oldLength = values.length();
	if(newLength==oldLength)
		return;

	IVector3 lastValue(IVector3::ZERO);
	if(newLength>oldLength && values.length()!=0)
		lastValue = values.back();

	values.resize(newLength);
	for(int i=oldLength; i<values.length(); i++)
		values[i] = lastValue;

	destroyElementsUI();
	createElementsUI();

	wxArrayIVector3SpinnerCtrlEvent event(wxEVT_COMMAND_ARRAY_IVECTOR3_SPINNER_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(values);
	
	GetEventHandler()->ProcessEvent( event );
}

void wxArrayIVector3SpinnerCtrl::onLengthChanged(wxArrayLengthCtrlEvent &evt)
{
	int newLength = evt.GetLength();
	
	resizeElementsUI(newLength);

	this->OnStateChange(this->GetBestSize());
}

void wxArrayIVector3SpinnerCtrl::onIVector3ValueChanged(wxIVector3SpinnerCtrlEvent &evt)
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

	wxArrayIVector3SpinnerCtrlEvent event(wxEVT_COMMAND_ARRAY_IVECTOR3_SPINNER_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(values);
	
	GetEventHandler()->ProcessEvent( event );
}