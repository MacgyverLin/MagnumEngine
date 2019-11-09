#include "wxArrayIVector2SpinnerCtrl.h"

////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC_CLASS( wxArrayIVector2SpinnerCtrlEvent, wxNotifyEvent )
DEFINE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_IVECTOR2_SPINNER_CTRL_VALUE_CHANGED )
////////////////////////////////////////////////////////////////////////////////////////

wxArrayIVector2SpinnerCtrl::wxArrayIVector2SpinnerCtrl(wxWindow *parent_, wxWindowID id_,
												     const char *label_,
												     const Vector<IVector2> &values_, const IVector2 &minValue_, const IVector2 &maxValue_,
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
	numElementsSpinner->Connect(wxEVT_COMMAND_ARRAY_LENGTH_CTRL_VALUE_CHANGED, wxArrayLengthCtrlHandler(wxArrayIVector2SpinnerCtrl::onLengthChanged)		, 0, this);
	
	createElementsUI();
}

void wxArrayIVector2SpinnerCtrl::setLength(int length_)
{
	resizeElementsUI(length_);
}

int wxArrayIVector2SpinnerCtrl::getLength() const
{
	return vector2Spinners.length();
}

void wxArrayIVector2SpinnerCtrl::setMinValue(const IVector2 &minValue_)
{
	minValue = minValue_;

	for(int i=0; i<vector2Spinners.length(); i++)
		vector2Spinners[i]->setMinValue(minValue_);
}

IVector2 wxArrayIVector2SpinnerCtrl::getMinValue() const
{
	return minValue;
}

void wxArrayIVector2SpinnerCtrl::setMaxValue(const IVector2 &maxValue_)
{
	maxValue = maxValue_;

	for(int i=0; i<vector2Spinners.length(); i++)
		vector2Spinners[i]->setMaxValue(maxValue);
}

IVector2 wxArrayIVector2SpinnerCtrl::getMaxValue() const
{
	return maxValue;
}

void wxArrayIVector2SpinnerCtrl::setValue(int idx, const IVector2 &value_)
{
	values[idx] = value_;
	vector2Spinners[idx]->setValue(value_);
}

IVector2 wxArrayIVector2SpinnerCtrl::getValue(int idx) const
{
	return vector2Spinners[idx]->getValue();
}

void wxArrayIVector2SpinnerCtrl::createElementsUI()
{
	wxWindow *contentPanel = this->GetPane();

	vector2Spinners.resize(values.length());
	for(int i=0; i<vector2Spinners.length(); i++)
	{
		wxString str;
		str.Printf("Element%d", i);
		vector2Spinners[i] = new wxIVector2SpinnerCtrl(contentPanel, wxID_ANY, 
			                                           str, true, 
													   values[i], minValue, maxValue, 
													   this->GetTopLevelWindow(),
			                                           wxDefaultPosition, wxDefaultSize);
		flexSizer->Add(vector2Spinners[i], 1, wxBOTTOM | wxEXPAND, 4);

		vector2Spinners[i]->Connect(wxEVT_COMMAND_IVECTOR2_SPINNER_CTRL_VALUE_CHANGED, wxIVector2SpinnerCtrlEventHandler(wxArrayIVector2SpinnerCtrl::onIVector2ValueChanged)		, 0, this);
	}
}

void wxArrayIVector2SpinnerCtrl::destroyElementsUI()
{
	for(int i=0; i<vector2Spinners.length(); i++)
	{
		delete vector2Spinners[i];
	}
	vector2Spinners.destroy();
}

void wxArrayIVector2SpinnerCtrl::resizeElementsUI(int newLength)
{
	int oldLength = values.length();
	if(newLength==oldLength)
		return;

	IVector2 lastValue(IVector2::ZERO);
	if(newLength>oldLength && values.length()!=0)
		lastValue = values.back();

	values.resize(newLength);
	for(int i=oldLength; i<values.length(); i++)
		values[i] = lastValue;

	destroyElementsUI();
	createElementsUI();

	wxArrayIVector2SpinnerCtrlEvent event(wxEVT_COMMAND_ARRAY_IVECTOR2_SPINNER_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(values);
	
	GetEventHandler()->ProcessEvent( event );
}

void wxArrayIVector2SpinnerCtrl::onLengthChanged(wxArrayLengthCtrlEvent &evt)
{
	int newLength = evt.GetLength();
	
	resizeElementsUI(newLength);

	this->OnStateChange(this->GetBestSize());
}

void wxArrayIVector2SpinnerCtrl::onIVector2ValueChanged(wxIVector2SpinnerCtrlEvent &evt)
{
	int idx = 0;
	for(int i=0; i<vector2Spinners.length(); i++)
	{
		if(vector2Spinners[i]==evt.GetEventObject())
		{
			idx = i;
			break;
		}
	}

	values[idx] = evt.GetValue();

	wxArrayIVector2SpinnerCtrlEvent event(wxEVT_COMMAND_ARRAY_IVECTOR2_SPINNER_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(values);
	
	GetEventHandler()->ProcessEvent( event );
}