#include "wxArrayLengthCtrl.h"

////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC_CLASS( wxArrayLengthCtrlEvent, wxNotifyEvent )
DEFINE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_LENGTH_CTRL_VALUE_CHANGED )

////////////////////////////////////////////////////////////////////////////////////////
wxArrayLengthCtrl::wxArrayLengthCtrl(wxWindow *parent_, wxWindowID id_,
									 const char *label_,
									 unsigned int value_, 
									 const wxPoint& pos_,
									 const wxSize& size_,
									 long style_)
: wxPanel(parent_, id_, pos_, size_, style_)
, value(value_)
{
	SetForegroundColour(parent_->GetForegroundColour());
    SetBackgroundColour(parent_->GetBackgroundColour());

	staticText = new wxStaticText(this, wxID_ANY, label_       , wxDefaultPosition, wxDefaultSize);
	staticText->SetMinSize(wxSize(128, COLLAPSE_BUTTON_SIZE));
    staticText->SetForegroundColour(parent_->GetForegroundColour());
    staticText->SetBackgroundColour(parent_->GetBackgroundColour());
	
	wxString str;
	str.Printf("%d", value);
	textCtrl   = new wxTextCtrl  (this, wxID_ANY, str, wxDefaultPosition, wxDefaultSize, wxTE_RIGHT | wxTE_PROCESS_ENTER);
	textCtrl->SetMinSize(wxSize(120, COLLAPSE_BUTTON_SIZE));
    //textCtrl->SetForegroundColour(parent_->GetForegroundColour());
    //textCtrl->SetBackgroundColour(parent_->GetBackgroundColour());

	const wxChar *numbers[] = 
	{ 
		wxT("0"), wxT("1"), wxT("2"), wxT("3"), wxT("4"), 
		wxT("5"), wxT("6"), wxT("7"), wxT("8"), wxT("9")
	}; 
    wxTextValidator vld(wxFILTER_INCLUDE_CHAR_LIST);
	vld.SetIncludes(wxArrayString(10, numbers));
	textCtrl->SetValidator(vld);
	
	wxBoxSizer *boxSizer = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizer(boxSizer);
	boxSizer->Add(staticText, 0);
	boxSizer->Add(textCtrl  , 1, wxEXPAND);

	textCtrl->Connect	(wxEVT_COMMAND_TEXT_ENTER	, wxCommandEventHandler	(wxArrayLengthCtrl::OnTextEntered)	, 0, this);
}

void wxArrayLengthCtrl::setValue(unsigned int value_)
{
	value	= value_;

	wxString str;
	str.Printf("%d", value);
	textCtrl->SetValue(str);
}

unsigned int wxArrayLengthCtrl::getValue() const
{
	return value;
}

void wxArrayLengthCtrl::fireEvent()
{
	wxArrayLengthCtrlEvent event(wxEVT_COMMAND_ARRAY_LENGTH_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetLength(value);

	GetEventHandler()->ProcessEvent( event );
}

void wxArrayLengthCtrl::OnTextEntered(wxCommandEvent &evt)
{
	unsigned int newValue  = atoi(textCtrl->GetValue());

	setValue(newValue);
	
	Refresh();

	fireEvent();
}