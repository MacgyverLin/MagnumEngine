#include "wxResourcePathCtrl.h"
#include "ResourceImportDragDrop.h"

////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC_CLASS( wxResourcePathCtrlEvent, wxNotifyEvent )
DEFINE_EVENT_TYPE( wxEVT_COMMAND_RESOURCEPATH_CTRL_VALUE_CHANGED )
////////////////////////////////////////////////////////////////////////////////////////

class wxResourcePathCtrlResourceImportDropTarget : public ResourceImportDropTarget
{
public:
	wxResourcePathCtrlResourceImportDropTarget(wxResourcePathCtrl *ctrl_, const char *extension_)
	: ResourceImportDropTarget(extension_)
	, ctrl(ctrl_)
	{
	}

	virtual bool onDropResourceImport(const char *path, const char *extension)
	{
		return ctrl->onDropResourceImport(path, extension);
	}
private:
	wxResourcePathCtrl *ctrl;
};

////////////////////////////////////////////////////////////////////////////////////////
wxResourcePathCtrl::wxResourcePathCtrl(wxWindow *parent_, wxWindowID id_,
									   const char *label_, const ResourcePath &value_, 
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

	textCtrl   = new wxStaticText(this, wxID_ANY, value.getPath().text(), wxDefaultPosition, wxDefaultSize);
	textCtrl->SetMinSize(wxSize(120, COLLAPSE_BUTTON_SIZE));
    textCtrl->SetForegroundColour(parent_->GetForegroundColour());
    textCtrl->SetBackgroundColour(parent_->GetBackgroundColour());

	wxBoxSizer *hBox = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizer(hBox);
	hBox->Add(staticText , 0);
	hBox->Add(textCtrl, 1, wxEXPAND);

	wxResourcePathCtrlResourceImportDropTarget *dropTarget = new wxResourcePathCtrlResourceImportDropTarget(this, value.getExtension());

	//wxToolTip *tooltip = new wxToolTip(value.getPath().text());
	//this->SetToolTip(tooltip);
	this->SetToolTip(wxString(value.getPath().text()));

	this->SetDropTarget(dropTarget);
}

void wxResourcePathCtrl::setValue(const ResourcePath &value_)
{
	value = value_;
	
	wxToolTip::Enable(true);

	this->SetToolTip(wxString(value.getPath().text()));
	textCtrl->SetLabel(value.getPath().text());
}

ResourcePath wxResourcePathCtrl::getValue() const
{
	return value;
}

void wxResourcePathCtrl::fireEvent()
{
	wxResourcePathCtrlEvent event(wxEVT_COMMAND_RESOURCEPATH_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(value);
	
	GetEventHandler()->ProcessEvent( event );
}

bool wxResourcePathCtrl::onDropResourceImport(const char *path, const char *extension)
{
	this->setValue(ResourcePath(path, extension));

	fireEvent();

	return true;
}