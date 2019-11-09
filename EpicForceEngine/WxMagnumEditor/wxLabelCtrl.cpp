#include "wxLabelCtrl.h"
#include "wxColorDlg.h"

////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC_CLASS( wxLabelCtrlEvent, wxNotifyEvent )
DEFINE_EVENT_TYPE( wxEVT_COMMAND_LABEL_CTRL_VALUE_CHANGED )

////////////////////////////////////////////////////////////////////////////////////////
wxLabelCtrl::wxLabelCtrl(wxWindow *parent_, wxWindowID id_,
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

	textCtrl   = new wxStaticText(this, wxID_ANY, value_.text(), wxDefaultPosition, wxDefaultSize);
	textCtrl->SetMinSize(wxSize(120, COLLAPSE_BUTTON_SIZE));
    textCtrl->SetForegroundColour(parent_->GetForegroundColour());
    textCtrl->SetBackgroundColour(parent_->GetBackgroundColour());

	wxBoxSizer *boxSizer = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizer(boxSizer);
	boxSizer->Add(staticText , 0);
	boxSizer->Add(textCtrl, 1, wxEXPAND);
}

void wxLabelCtrl::setValue(const String &value_)
{
	value = value_;

	textCtrl->SetLabel(value.text());
}

String wxLabelCtrl::getValue() const
{
	return value;
}