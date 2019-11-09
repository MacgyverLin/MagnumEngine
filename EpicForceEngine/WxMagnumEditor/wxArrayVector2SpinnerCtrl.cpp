#include "wxArrayVector2SpinnerCtrl.h"

////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC_CLASS( wxArrayVector2SpinnerCtrlEvent, wxNotifyEvent )
DEFINE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_VECTOR2_SPINNER_CTRL_VALUE_CHANGED )
////////////////////////////////////////////////////////////////////////////////////////

wxArrayVector2SpinnerCtrl::wxArrayVector2SpinnerCtrl(wxWindow *parent_, wxWindowID id_,
												     const char *label_,
												     const Vector<Vector2> &values_, const Vector2 &minValue_, const Vector2 &maxValue_,
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
	numElementsSpinner->Connect(wxEVT_COMMAND_ARRAY_LENGTH_CTRL_VALUE_CHANGED, wxArrayLengthCtrlHandler(wxArrayVector2SpinnerCtrl::onLengthChanged)		, 0, this);
	
	createElementsUI();
}

void wxArrayVector2SpinnerCtrl::setLength(int length_)
{
	resizeElementsUI(length_);
}

int wxArrayVector2SpinnerCtrl::getLength() const
{
	return vector2Spinners.length();
}

void wxArrayVector2SpinnerCtrl::setMinValue(const Vector2 &minValue_)
{
	minValue = minValue_;

	for(int i=0; i<vector2Spinners.length(); i++)
		vector2Spinners[i]->setMinValue(minValue_);
}

Vector2 wxArrayVector2SpinnerCtrl::getMinValue() const
{
	return minValue;
}

void wxArrayVector2SpinnerCtrl::setMaxValue(const Vector2 &maxValue_)
{
	maxValue = maxValue_;

	for(int i=0; i<vector2Spinners.length(); i++)
		vector2Spinners[i]->setMaxValue(maxValue);
}

Vector2 wxArrayVector2SpinnerCtrl::getMaxValue() const
{
	return maxValue;
}

void wxArrayVector2SpinnerCtrl::setValue(int idx, const Vector2 &value_)
{
	values[idx] = value_;
	vector2Spinners[idx]->setValue(value_);
}

Vector2 wxArrayVector2SpinnerCtrl::getValue(int idx) const
{
	return vector2Spinners[idx]->getValue();
}

void wxArrayVector2SpinnerCtrl::createElementsUI()
{
	wxWindow *contentPanel = this->GetPane();

	vector2Spinners.resize(values.length());
	for(int i=0; i<vector2Spinners.length(); i++)
	{
		wxString str;
		str.Printf("Element%d", i);
		vector2Spinners[i] = new wxVector2SpinnerCtrl(contentPanel, wxID_ANY, 
			                                          str, true,
													  values[i], minValue, maxValue, 
													  this->GetTopLevelWindow(),
			                                          wxDefaultPosition, wxDefaultSize);
		flexSizer->Add(vector2Spinners[i], 1, wxBOTTOM | wxEXPAND, 4);

		vector2Spinners[i]->Connect(wxEVT_COMMAND_VECTOR2_SPINNER_CTRL_VALUE_CHANGED, wxVector2SpinnerCtrlEventHandler(wxArrayVector2SpinnerCtrl::onVector2ValueChanged)		, 0, this);
	}
}

void wxArrayVector2SpinnerCtrl::destroyElementsUI()
{
	for(int i=0; i<vector2Spinners.length(); i++)
	{
		delete vector2Spinners[i];
	}
	vector2Spinners.destroy();
}

void wxArrayVector2SpinnerCtrl::resizeElementsUI(int newLength)
{
	int oldLength = values.length();
	if(newLength==oldLength)
		return;

	Vector2 lastValue(Vector2::ZERO);
	if(newLength>oldLength && values.length()!=0)
		lastValue = values.back();

	values.resize(newLength);
	for(int i=oldLength; i<values.length(); i++)
		values[i] = lastValue;

	destroyElementsUI();
	createElementsUI();

	wxArrayVector2SpinnerCtrlEvent event(wxEVT_COMMAND_ARRAY_VECTOR2_SPINNER_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(values);
	
	GetEventHandler()->ProcessEvent( event );
}

void wxArrayVector2SpinnerCtrl::onLengthChanged(wxArrayLengthCtrlEvent &evt)
{
	int newLength = evt.GetLength();
	
	resizeElementsUI(newLength);

	this->OnStateChange(this->GetBestSize());
}

void wxArrayVector2SpinnerCtrl::onVector2ValueChanged(wxVector2SpinnerCtrlEvent &evt)
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

	wxArrayVector2SpinnerCtrlEvent event(wxEVT_COMMAND_ARRAY_VECTOR2_SPINNER_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(values);
	
	GetEventHandler()->ProcessEvent( event );
}