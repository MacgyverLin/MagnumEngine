#include "wxArrayIVector4SpinnerCtrl.h"

////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC_CLASS( wxArrayIVector4SpinnerCtrlEvent, wxNotifyEvent )
DEFINE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_IVECTOR4_SPINNER_CTRL_VALUE_CHANGED )
////////////////////////////////////////////////////////////////////////////////////////

wxArrayIVector4SpinnerCtrl::wxArrayIVector4SpinnerCtrl(wxWindow *parent_, wxWindowID id_,
												     const char *label_,
												     const Vector<IVector4> &values_, const IVector4 &minValue_, const IVector4 &maxValue_,
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
	numElementsSpinner->Connect(wxEVT_COMMAND_ARRAY_LENGTH_CTRL_VALUE_CHANGED, wxArrayLengthCtrlHandler(wxArrayIVector4SpinnerCtrl::onLengthChanged)		, 0, this);
	
	createElementsUI();
}

void wxArrayIVector4SpinnerCtrl::setLength(int length_)
{
	resizeElementsUI(length_);
}

int wxArrayIVector4SpinnerCtrl::getLength() const
{
	return vector4Spinners.length();
}

void wxArrayIVector4SpinnerCtrl::setMinValue(const IVector4 &minValue_)
{
	minValue = minValue_;

	for(int i=0; i<vector4Spinners.length(); i++)
		vector4Spinners[i]->setMinValue(minValue_);
}

IVector4 wxArrayIVector4SpinnerCtrl::getMinValue() const
{
	return minValue;
}

void wxArrayIVector4SpinnerCtrl::setMaxValue(const IVector4 &maxValue_)
{
	maxValue = maxValue_;

	for(int i=0; i<vector4Spinners.length(); i++)
		vector4Spinners[i]->setMaxValue(maxValue);
}

IVector4 wxArrayIVector4SpinnerCtrl::getMaxValue() const
{
	return maxValue;
}

void wxArrayIVector4SpinnerCtrl::setValue(int idx, const IVector4 &value_)
{
	values[idx] = value_;
	vector4Spinners[idx]->setValue(value_);
}

IVector4 wxArrayIVector4SpinnerCtrl::getValue(int idx) const
{
	return vector4Spinners[idx]->getValue();
}

void wxArrayIVector4SpinnerCtrl::createElementsUI()
{
	wxWindow *contentPanel = this->GetPane();

	vector4Spinners.resize(values.length());
	for(int i=0; i<vector4Spinners.length(); i++)
	{
		wxString str;
		str.Printf("Element%d", i);
		vector4Spinners[i] = new wxIVector4SpinnerCtrl(contentPanel, wxID_ANY, 
			                                           str, true,
													   values[i], minValue, maxValue, 
													   this->GetTopLevelWindow(),
			                                           wxDefaultPosition, wxDefaultSize);
		flexSizer->Add(vector4Spinners[i], 1, wxBOTTOM | wxEXPAND, 4);

		vector4Spinners[i]->Connect(wxEVT_COMMAND_IVECTOR4_SPINNER_CTRL_VALUE_CHANGED, wxIVector4SpinnerCtrlEventHandler(wxArrayIVector4SpinnerCtrl::onIVector4ValueChanged)		, 0, this);
	}
}

void wxArrayIVector4SpinnerCtrl::destroyElementsUI()
{
	for(int i=0; i<vector4Spinners.length(); i++)
	{
		delete vector4Spinners[i];
	}
	vector4Spinners.destroy();
}

void wxArrayIVector4SpinnerCtrl::resizeElementsUI(int newLength)
{
	int oldLength = values.length();
	if(newLength==oldLength)
		return;

	IVector4 lastValue(IVector4::ZERO);
	if(newLength>oldLength && values.length()!=0)
		lastValue = values.back();

	values.resize(newLength);
	for(int i=oldLength; i<values.length(); i++)
		values[i] = lastValue;

	destroyElementsUI();
	createElementsUI();

	wxArrayIVector4SpinnerCtrlEvent event(wxEVT_COMMAND_ARRAY_IVECTOR4_SPINNER_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(values);
	
	GetEventHandler()->ProcessEvent( event );
}

void wxArrayIVector4SpinnerCtrl::onLengthChanged(wxArrayLengthCtrlEvent &evt)
{
	int newLength = evt.GetLength();
	
	resizeElementsUI(newLength);

	this->OnStateChange(this->GetBestSize());
}

void wxArrayIVector4SpinnerCtrl::onIVector4ValueChanged(wxIVector4SpinnerCtrlEvent &evt)
{
	int idx = 0;
	for(int i=0; i<vector4Spinners.length(); i++)
	{
		if(vector4Spinners[i]==evt.GetEventObject())
		{
			idx = i;
			break;
		}
	}

	values[idx] = evt.GetValue();

	wxArrayIVector4SpinnerCtrlEvent event(wxEVT_COMMAND_ARRAY_IVECTOR4_SPINNER_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(values);
	
	GetEventHandler()->ProcessEvent( event );
}