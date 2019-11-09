#include "wxArrayStringCtrl.h"

////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC_CLASS( wxArrayStringCtrlEvent, wxNotifyEvent )
DEFINE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_STRING_CTRL_VALUE_CHANGED )
////////////////////////////////////////////////////////////////////////////////////////

wxArrayStringCtrl::wxArrayStringCtrl(wxWindow *parent_, wxWindowID id_,
								     const char *label_,
								     const Vector<String> &values_, 
								     wxWindow *topLevelWindow_,
								     const wxPoint &pos_, const wxSize &size_,
								     long style_)
: wxCollapsePanelCtrl(parent_, id_, label_, topLevelWindow_, pos_, size_, style_)
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
	numElementsSpinner->Connect(wxEVT_COMMAND_ARRAY_LENGTH_CTRL_VALUE_CHANGED, wxArrayLengthCtrlHandler(wxArrayStringCtrl::onLengthChanged)		, 0, this);
	
	createElementsUI();
}

void wxArrayStringCtrl::setLength(int length_)
{
	resizeElementsUI(length_);
}

int wxArrayStringCtrl::getLength() const
{
	return stringCtrls.length();
}

void wxArrayStringCtrl::setValue(int idx, const String &value_)
{
	values[idx] = value_;
	stringCtrls[idx]->setValue(value_);
}

String wxArrayStringCtrl::getValue(int idx) const
{
	return stringCtrls[idx]->getValue();
}

void wxArrayStringCtrl::createElementsUI()
{
	wxWindow *contentPanel = this->GetPane();

	stringCtrls.resize(values.length());
	for(int i=0; i<stringCtrls.length(); i++)
	{
		wxString str;
		str.Printf("Element%d", i);
		stringCtrls[i] = new wxStringCtrl(contentPanel, wxID_ANY, 
			                            str, values[i]);
		flexSizer->Add(stringCtrls[i], 1, wxBOTTOM | wxEXPAND, 4);

		stringCtrls[i]->Connect(wxEVT_COMMAND_STRING_CTRL_VALUE_CHANGED, wxStringCtrlEventHandler(wxArrayStringCtrl::onStringValueChanged)		, 0, this);
	}
}

void wxArrayStringCtrl::destroyElementsUI()
{
	for(int i=0; i<stringCtrls.length(); i++)
	{
		delete stringCtrls[i];
	}
	stringCtrls.destroy();
}

void wxArrayStringCtrl::resizeElementsUI(int newLength)
{
	int oldLength = values.length();
	if(newLength==oldLength)
		return;

	String lastValue;
	if(newLength>oldLength && values.length()!=0)
		lastValue = values.back();

	values.resize(newLength);
	for(int i=oldLength; i<values.length(); i++)
		values[i] = lastValue;

	destroyElementsUI();
	createElementsUI();

	wxArrayStringCtrlEvent event(wxEVT_COMMAND_ARRAY_STRING_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(values);
	
	GetEventHandler()->ProcessEvent( event );
}

void wxArrayStringCtrl::onLengthChanged(wxArrayLengthCtrlEvent &evt)
{
	int newLength = evt.GetLength();
	
	resizeElementsUI(newLength);

	this->OnStateChange(this->GetBestSize());
}

void wxArrayStringCtrl::onStringValueChanged(wxStringCtrlEvent &evt)
{
	int idx = 0;
	for(int i=0; i<stringCtrls.length(); i++)
	{
		if(stringCtrls[i]==evt.GetEventObject())
		{
			idx = i;
			break;
		}
	}

	values[idx] = evt.GetValue();

	wxArrayStringCtrlEvent event(wxEVT_COMMAND_ARRAY_STRING_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(values);
	
	GetEventHandler()->ProcessEvent( event );
}