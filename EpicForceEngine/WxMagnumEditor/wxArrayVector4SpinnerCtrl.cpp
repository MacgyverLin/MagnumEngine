#include "wxArrayVector4SpinnerCtrl.h"

////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC_CLASS( wxArrayVector4SpinnerCtrlEvent, wxNotifyEvent )
DEFINE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_VECTOR4_SPINNER_CTRL_VALUE_CHANGED )
////////////////////////////////////////////////////////////////////////////////////////

wxArrayVector4SpinnerCtrl::wxArrayVector4SpinnerCtrl(wxWindow *parent_, wxWindowID id_,
												     const char *label_,
												     const Vector<Vector4> &values_, const Vector4 &minValue_, const Vector4 &maxValue_,
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
	numElementsSpinner->Connect(wxEVT_COMMAND_ARRAY_LENGTH_CTRL_VALUE_CHANGED, wxArrayLengthCtrlHandler(wxArrayVector4SpinnerCtrl::onLengthChanged)		, 0, this);
	
	createElementsUI();
}

void wxArrayVector4SpinnerCtrl::setLength(int length_)
{
	resizeElementsUI(length_);
}

int wxArrayVector4SpinnerCtrl::getLength() const
{
	return vector4Spinners.length();
}

void wxArrayVector4SpinnerCtrl::setMinValue(const Vector4 &minValue_)
{
	minValue = minValue_;

	for(int i=0; i<vector4Spinners.length(); i++)
		vector4Spinners[i]->setMinValue(minValue_);
}

Vector4 wxArrayVector4SpinnerCtrl::getMinValue() const
{
	return minValue;
}

void wxArrayVector4SpinnerCtrl::setMaxValue(const Vector4 &maxValue_)
{
	maxValue = maxValue_;

	for(int i=0; i<vector4Spinners.length(); i++)
		vector4Spinners[i]->setMaxValue(maxValue);
}

Vector4 wxArrayVector4SpinnerCtrl::getMaxValue() const
{
	return maxValue;
}

void wxArrayVector4SpinnerCtrl::setValue(int idx, const Vector4 &value_)
{
	values[idx] = value_;
	vector4Spinners[idx]->setValue(value_);
}

Vector4 wxArrayVector4SpinnerCtrl::getValue(int idx) const
{
	return vector4Spinners[idx]->getValue();
}

void wxArrayVector4SpinnerCtrl::createElementsUI()
{
	wxWindow *contentPanel = this->GetPane();

	vector4Spinners.resize(values.length());
	for(int i=0; i<vector4Spinners.length(); i++)
	{
		wxString str;
		str.Printf("Element%d", i);
		vector4Spinners[i] = new wxVector4SpinnerCtrl(contentPanel, wxID_ANY, 
			                                          str, true,
													  values[i], minValue, maxValue, 
													  this->GetTopLevelWindow(),
			                                          wxDefaultPosition, wxDefaultSize);
		flexSizer->Add(vector4Spinners[i], 1, wxBOTTOM | wxEXPAND, 4);

		vector4Spinners[i]->Connect(wxEVT_COMMAND_VECTOR4_SPINNER_CTRL_VALUE_CHANGED, wxVector4SpinnerCtrlEventHandler(wxArrayVector4SpinnerCtrl::onVector4ValueChanged)		, 0, this);
	}
}

void wxArrayVector4SpinnerCtrl::destroyElementsUI()
{
	for(int i=0; i<vector4Spinners.length(); i++)
	{
		delete vector4Spinners[i];
	}
	vector4Spinners.destroy();
}

void wxArrayVector4SpinnerCtrl::resizeElementsUI(int newLength)
{
	int oldLength = values.length();
	if(newLength==oldLength)
		return;

	Vector4 lastValue(Vector4::ZERO);
	if(newLength>oldLength && values.length()!=0)
		lastValue = values.back();

	values.resize(newLength);
	for(int i=oldLength; i<values.length(); i++)
		values[i] = lastValue;

	destroyElementsUI();
	createElementsUI();

	wxArrayVector4SpinnerCtrlEvent event(wxEVT_COMMAND_ARRAY_VECTOR4_SPINNER_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(values);
	
	GetEventHandler()->ProcessEvent( event );
}

void wxArrayVector4SpinnerCtrl::onLengthChanged(wxArrayLengthCtrlEvent &evt)
{
	int newLength = evt.GetLength();
	
	resizeElementsUI(newLength);

	this->OnStateChange(this->GetBestSize());
}

void wxArrayVector4SpinnerCtrl::onVector4ValueChanged(wxVector4SpinnerCtrlEvent &evt)
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

	wxArrayVector4SpinnerCtrlEvent event(wxEVT_COMMAND_ARRAY_VECTOR4_SPINNER_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(values);
	
	GetEventHandler()->ProcessEvent( evt );
}