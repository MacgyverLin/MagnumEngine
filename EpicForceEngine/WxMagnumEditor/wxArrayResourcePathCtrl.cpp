#include "wxArrayResourcePathCtrl.h"

////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC_CLASS( wxArrayResourcePathCtrlEvent, wxNotifyEvent )
DEFINE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_RESOURCEPATH_CTRL_VALUE_CHANGED )
////////////////////////////////////////////////////////////////////////////////////////

wxArrayResourcePathCtrl::wxArrayResourcePathCtrl(wxWindow *parent_, wxWindowID id_,
									       const char *label_,
										   const Vector<ResourcePath> &values_, 
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
	numElementsSpinner->Connect(wxEVT_COMMAND_ARRAY_LENGTH_CTRL_VALUE_CHANGED, wxArrayLengthCtrlHandler(wxArrayResourcePathCtrl::onLengthChanged)		, 0, this);
	
	createElementsUI();
}

void wxArrayResourcePathCtrl::setLength(int length_)
{
	resizeElementsUI(length_);
}

int wxArrayResourcePathCtrl::getLength() const
{
	return resourcePathCtrls.length();
}

void wxArrayResourcePathCtrl::setValue(int idx, const ResourcePath &value_)
{
	values[idx] = value_;
	resourcePathCtrls[idx]->setValue(value_);
}

ResourcePath wxArrayResourcePathCtrl::getValue(int idx) const
{
	return resourcePathCtrls[idx]->getValue();
}

void wxArrayResourcePathCtrl::createElementsUI()
{
	wxWindow *contentPanel = this->GetPane();

	resourcePathCtrls.resize(values.length());
	for(int i=0; i<resourcePathCtrls.length(); i++)
	{
		wxString str;
		str.Printf("Element%d", i);
		resourcePathCtrls[i] = new wxResourcePathCtrl(contentPanel, wxID_ANY, 
			                                    str, 
												values[i], 
			                                    wxDefaultPosition, wxDefaultSize);
		flexSizer->Add(resourcePathCtrls[i], 1, wxBOTTOM | wxEXPAND, 4);

		resourcePathCtrls[i]->Connect(wxEVT_COMMAND_RESOURCEPATH_CTRL_VALUE_CHANGED, wxResourcePathCtrlEventHandler(wxArrayResourcePathCtrl::onResourcePathValueChanged)		, 0, this);
	}
}

void wxArrayResourcePathCtrl::destroyElementsUI()
{
	for(int i=0; i<resourcePathCtrls.length(); i++)
	{
		delete resourcePathCtrls[i];
	}
	resourcePathCtrls.destroy();
}

void wxArrayResourcePathCtrl::resizeElementsUI(int newLength)
{
	int oldLength = values.length();
	if(newLength==oldLength)
		return;

	ResourcePath lastValue;
	if(newLength>oldLength && values.length()!=0)
		lastValue = values.back();

	values.resize(newLength);
	for(int i=oldLength; i<values.length(); i++)
		values[i] = lastValue;

	destroyElementsUI();
	createElementsUI();

	wxArrayResourcePathCtrlEvent event(wxEVT_COMMAND_ARRAY_RESOURCEPATH_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(values);
	
	GetEventHandler()->ProcessEvent( event );
}

void wxArrayResourcePathCtrl::onLengthChanged(wxArrayLengthCtrlEvent &evt)
{
	int newLength = evt.GetLength();
	
	resizeElementsUI(newLength);

	this->OnStateChange(this->GetBestSize());
}

void wxArrayResourcePathCtrl::onResourcePathValueChanged(wxResourcePathCtrlEvent &evt)
{
	int idx = 0;
	for(int i=0; i<resourcePathCtrls.length(); i++)
	{
		if(resourcePathCtrls[i]==evt.GetEventObject())
		{
			idx = i;
			break;
		}
	}

	values[idx] = evt.GetValue();

	wxArrayResourcePathCtrlEvent event(wxEVT_COMMAND_ARRAY_RESOURCEPATH_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(values);
	
	GetEventHandler()->ProcessEvent( event );
}