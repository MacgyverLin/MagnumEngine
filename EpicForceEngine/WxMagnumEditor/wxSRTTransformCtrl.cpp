#include "wxSRTTransformCtrl.h"

////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC_CLASS( wxSRTTransformCtrlEvent, wxNotifyEvent )
DEFINE_EVENT_TYPE( wxEVT_COMMAND_SRTTRANSFORM_CTRL_VALUE_CHANGED )

////////////////////////////////////////////////////////////////////////////////////////
wxSRTTransformCtrl::wxSRTTransformCtrl(wxWindow *parent_, wxWindowID id_,
									   const char *label_, 
									   const SRTTransform &value_,
									   wxWindow *topLevelWindow_,
									   const wxPoint &pos_, const wxSize &size_,
									   long style_)
: wxCollapsePanelCtrl(parent_, id_, label_, topLevelWindow_, pos_, size_, style_)
, vector3Spinners(3)
{
	this->SetBackgroundColour(parent_->GetBackgroundColour());
	this->SetForegroundColour(parent_->GetForegroundColour());

	wxWindow *contentPanel = this->GetPane();

	hBox		= new wxBoxSizer(wxHORIZONTAL);
	flexSizer	= new wxFlexGridSizer(1); flexSizer->AddGrowableCol(0);
	contentPanel->SetSizer(hBox);
		hBox->Add(COLLAPSE_BUTTON_SIZE*1.5, COLLAPSE_BUTTON_SIZE, 0);
		hBox->Add(flexSizer, 1, wxEXPAND);

	vector3Spinners[0] = new wxVector3SpinnerCtrl(contentPanel, wxID_ANY, 
												  "Position", false, 
												  value_.T(), Vector3(Math::MIN_REAL, Math::MIN_REAL, Math::MIN_REAL), Vector3(Math::MAX_REAL, Math::MAX_REAL, Math::MAX_REAL),
												  this);

	vector3Spinners[1] = new wxVector3SpinnerCtrl(contentPanel, wxID_ANY, 
												  "Rotation", false, 
												  value_.R(), Vector3(Math::MIN_REAL, Math::MIN_REAL, Math::MIN_REAL), Vector3(Math::MAX_REAL, Math::MAX_REAL, Math::MAX_REAL),
												  this);

	vector3Spinners[2] = new wxVector3SpinnerCtrl(contentPanel, wxID_ANY, 
												  "Scale", false, 
												  value_.S(), Vector3(Math::MIN_REAL, Math::MIN_REAL, Math::MIN_REAL), Vector3(Math::MAX_REAL, Math::MAX_REAL, Math::MAX_REAL),
												  this);

	flexSizer->Add(vector3Spinners[0], 0, wxEXPAND);
	flexSizer->Add(vector3Spinners[1], 0, wxEXPAND);
	flexSizer->Add(vector3Spinners[2], 0, wxEXPAND);

	vector3Spinners[0]->Connect(wxEVT_COMMAND_VECTOR3_SPINNER_CTRL_VALUE_CHANGED, wxVector3SpinnerCtrlEventHandler(wxSRTTransformCtrl::onPositionValueChanged), 0, this);
	vector3Spinners[1]->Connect(wxEVT_COMMAND_VECTOR3_SPINNER_CTRL_VALUE_CHANGED, wxVector3SpinnerCtrlEventHandler(wxSRTTransformCtrl::onRotationValueChanged), 0, this);
	vector3Spinners[2]->Connect(wxEVT_COMMAND_VECTOR3_SPINNER_CTRL_VALUE_CHANGED, wxVector3SpinnerCtrlEventHandler(wxSRTTransformCtrl::onScaleValueChanged), 0, this);

	this->Collapse(false);
}

void wxSRTTransformCtrl::setValue(const SRTTransform &value_)
{
	vector3Spinners[0]->setValue(value_.T()	);
	vector3Spinners[1]->setValue(value_.R()	);
	vector3Spinners[2]->setValue(value_.S()	);
}

SRTTransform wxSRTTransformCtrl::getValue() const
{
	SRTTransform rval;

	rval.T() = vector3Spinners[0]->getValue();
	rval.R() = vector3Spinners[1]->getValue();
	rval.S() = vector3Spinners[2]->getValue();

	return rval;
}

void wxSRTTransformCtrl::onPositionValueChanged(wxVector3SpinnerCtrlEvent &evt)
{
	wxSRTTransformCtrlEvent event(wxEVT_COMMAND_SRTTRANSFORM_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());

	SRTTransform srtTransform(getValue());
	srtTransform.changed = 1;
	event.SetValue(srtTransform);

	GetEventHandler()->ProcessEvent( event );
}

void wxSRTTransformCtrl::onRotationValueChanged(wxVector3SpinnerCtrlEvent &evt)
{
	wxSRTTransformCtrlEvent event(wxEVT_COMMAND_SRTTRANSFORM_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());

	SRTTransform srtTransform(getValue());
	srtTransform.changed = 2;
	event.SetValue(srtTransform);

	GetEventHandler()->ProcessEvent( event );
}

void wxSRTTransformCtrl::onScaleValueChanged(wxVector3SpinnerCtrlEvent &evt)
{
	wxSRTTransformCtrlEvent event(wxEVT_COMMAND_SRTTRANSFORM_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());

	SRTTransform srtTransform(getValue());
	srtTransform.changed = 3;
	event.SetValue(srtTransform);

	GetEventHandler()->ProcessEvent( event );
}