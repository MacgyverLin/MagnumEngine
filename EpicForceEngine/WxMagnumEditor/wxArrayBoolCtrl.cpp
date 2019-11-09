#include "wxArrayBoolCtrl.h"

////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC_CLASS( wxArrayBoolCtrlEvent, wxNotifyEvent )
DEFINE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_BOOL_CTRL_VALUE_CHANGED )
////////////////////////////////////////////////////////////////////////////////////////

wxArrayBoolCtrl::wxArrayBoolCtrl(wxWindow *parent_, wxWindowID id_,
								 const char *label_,
								 const Vector<bool> &values_, 
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
	numElementsSpinner->Connect(wxEVT_COMMAND_ARRAY_LENGTH_CTRL_VALUE_CHANGED, wxArrayLengthCtrlHandler(wxArrayBoolCtrl::onLengthChanged)		, 0, this);
	
	createElementsUI();
}

void wxArrayBoolCtrl::setLength(int length_)
{
	resizeElementsUI(length_);
}

int wxArrayBoolCtrl::getLength() const
{
	return boolCtrls.length();
}

void wxArrayBoolCtrl::setValue(int idx, bool value_)
{
	values[idx] = value_;
	boolCtrls[idx]->setValue(value_);
}

bool wxArrayBoolCtrl::getValue(int idx) const
{
	return boolCtrls[idx]->getValue();
}

void wxArrayBoolCtrl::createElementsUI()
{
	wxWindow *contentPanel = this->GetPane();

	boolCtrls.resize(values.length());
	for(int i=0; i<boolCtrls.length(); i++)
	{
		wxString str;
		str.Printf("Element%d", i);
		boolCtrls[i] = new wxBoolCtrl(contentPanel, wxID_ANY, str, values[i]);
		flexSizer->Add(boolCtrls[i], 1, wxBOTTOM | wxEXPAND, 4);

		boolCtrls[i]->Connect(wxEVT_COMMAND_BOOL_CTRL_VALUE_CHANGED, wxBoolCtrlEventHandler(wxArrayBoolCtrl::onBoolValueChanged)		, 0, this);
	}
}

void wxArrayBoolCtrl::destroyElementsUI()
{
	for(int i=0; i<boolCtrls.length(); i++)
	{
		delete boolCtrls[i];
	}
	boolCtrls.destroy();
}

void wxArrayBoolCtrl::resizeElementsUI(int newLength)
{
	int oldLength = values.length();
	if(newLength==oldLength)
		return;

	bool lastValue = 0;
	if(newLength>oldLength && values.length()!=0)
		lastValue = values.back();

	values.resize(newLength);
	for(int i=oldLength; i<values.length(); i++)
		values[i] = lastValue;

	destroyElementsUI();
	createElementsUI();

	wxArrayBoolCtrlEvent event(wxEVT_COMMAND_ARRAY_BOOL_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(values);
	
	GetEventHandler()->ProcessEvent( event );
}

void wxArrayBoolCtrl::onLengthChanged(wxArrayLengthCtrlEvent &evt)
{
	int newLength = evt.GetLength();
	
	resizeElementsUI(newLength);

	this->OnStateChange(this->GetBestSize());
}

void wxArrayBoolCtrl::onBoolValueChanged(wxBoolCtrlEvent &evt)
{
	int idx = 0;
	for(int i=0; i<boolCtrls.length(); i++)
	{
		if(boolCtrls[i]==evt.GetEventObject())
		{
			idx = i;
			break;
		}
	}

	values[idx] = evt.GetValue();

	wxArrayBoolCtrlEvent event(wxEVT_COMMAND_ARRAY_BOOL_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(values);
	
	GetEventHandler()->ProcessEvent( event );
}