#include "wxStringCtrl.h"
#include "wxColorDlg.h"

////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC_CLASS( wxStringCtrlEvent, wxNotifyEvent )
DEFINE_EVENT_TYPE( wxEVT_COMMAND_STRING_CTRL_VALUE_CHANGED )

////////////////////////////////////////////////////////////////////////////////////////
wxStringCtrl::wxStringCtrl(wxWindow *parent_, wxWindowID id_,
						   const char *label_, const String &value_, 
						   const wxPoint &pos_, const wxSize &size_,
						   long style_)
: wxPanel(parent_, id_, pos_, size_, style_)
, value(value_)
{
	SetForegroundColour(parent_->GetForegroundColour());
    SetBackgroundColour(parent_->GetBackgroundColour());

	staticText = new wxStaticText(this, wxID_ANY, label_, wxDefaultPosition, wxDefaultSize);
	staticText->SetMinSize(wxSize(128, COLLAPSE_BUTTON_SIZE));
    staticText->SetForegroundColour(parent_->GetForegroundColour());
    staticText->SetBackgroundColour(parent_->GetBackgroundColour());	

	textCtrl   = new wxTextCtrl  (this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_RIGHT | wxTE_PROCESS_ENTER | wxBORDER_SIMPLE);
	textCtrl->SetMinSize(wxSize(120, COLLAPSE_BUTTON_SIZE));
	setValue(value_);
    wxTextValidator vld(wxFILTER_ASCII);
	textCtrl->SetValidator(vld);

	wxBoxSizer *hBox = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizer(hBox);
	hBox->Add(staticText , 0);
	hBox->Add(textCtrl, 1, wxEXPAND);

	textCtrl->Connect	(wxEVT_COMMAND_TEXT_ENTER	, wxCommandEventHandler	(wxStringCtrl::OnTextEntered)	, 0, this);
	//textCtrl->Connect	(wxEVT_COMMAND_TEXT_UPDATED	, wxCommandEventHandler	(wxStringCtrl::OnTextUpdated)	, 0, this);
}

void wxStringCtrl::setValue(const String &value_)
{
	value = value_;

	textCtrl->SetValue(value.text());
}

String wxStringCtrl::getValue() const
{
	return value;
}

void wxStringCtrl::OnTextEntered(wxCommandEvent &evt)
{
	String newValue  = textCtrl->GetValue().c_str();

	setValue(newValue);
	
	Refresh();

	fireEvent();
}

void wxStringCtrl::fireEvent()
{
	wxStringCtrlEvent event(wxEVT_COMMAND_STRING_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(value);

	GetEventHandler()->ProcessEvent( event );
}