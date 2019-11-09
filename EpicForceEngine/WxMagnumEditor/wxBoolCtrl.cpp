#include "wxBoolCtrl.h"

////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC_CLASS( wxBoolCtrlEvent, wxNotifyEvent )
DEFINE_EVENT_TYPE( wxEVT_COMMAND_BOOL_CTRL_VALUE_CHANGED )

////////////////////////////////////////////////////////////////////////////////////////
wxBoolCtrl::wxBoolCtrl(wxWindow *parent_, wxWindowID id_,
					   const char *label_, const bool &value_, 
					   const wxPoint &pos_, const wxSize &size_,
					   long style_)
: wxPanel(parent_, id_, pos_, size_, style_)
, value(value_)
{
	SetForegroundColour(parent_->GetForegroundColour());
    SetBackgroundColour(parent_->GetBackgroundColour());

	staticText = new wxStaticText(this, wxID_ANY, label_, wxDefaultPosition, wxDefaultSize);
    staticText->SetForegroundColour(parent_->GetForegroundColour());
    staticText->SetBackgroundColour(parent_->GetBackgroundColour());
	staticText->SetMinSize(wxSize(128, COLLAPSE_BUTTON_SIZE));

	checkBox = new wxCheckBox(this, wxID_ANY, ""   , wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
	checkBox->SetMinSize(wxSize(120, COLLAPSE_BUTTON_SIZE));
	setValue(value_);

	wxBoxSizer *hBox = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizer(hBox);
	hBox->Add(staticText , 0);
	hBox->Add(checkBox, 1, wxEXPAND);

	checkBox->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED 			, wxCommandEventHandler(wxBoolCtrl::OnChecked)		, 0, this);
}

void wxBoolCtrl::setValue(const bool &value_)
{
	value = value_;

	checkBox->SetValue(value);
}

bool wxBoolCtrl::getValue() const
{
	return value;
}

void wxBoolCtrl::fireEvent()
{
	wxBoolCtrlEvent event(wxEVT_COMMAND_BOOL_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(value);

	GetEventHandler()->ProcessEvent( event );
}

void wxBoolCtrl::OnChecked(wxCommandEvent &evt)
{
	value = evt.IsChecked();

	fireEvent();
}