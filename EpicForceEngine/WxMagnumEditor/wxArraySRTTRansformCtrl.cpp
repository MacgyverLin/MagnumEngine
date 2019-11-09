#include "wxArraySRTTransformCtrl.h"

////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC_CLASS( wxArraySRTTransformCtrlEvent, wxNotifyEvent )
DEFINE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_SRTTRANSFORM_CTRL_VALUE_CHANGED )
////////////////////////////////////////////////////////////////////////////////////////

wxArraySRTTransformCtrl::wxArraySRTTransformCtrl(wxWindow *parent_, wxWindowID id_,
												 const char *label_,
												 const Vector<SRTTransform> &values_,
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
	numElementsSpinner->Connect(wxEVT_COMMAND_ARRAY_LENGTH_CTRL_VALUE_CHANGED, wxArrayLengthCtrlHandler(wxArraySRTTransformCtrl::onLengthChanged)		, 0, this);
	
	createElementsUI();
}

void wxArraySRTTransformCtrl::setLength(int length_)
{
	resizeElementsUI(length_);
}

int wxArraySRTTransformCtrl::getLength() const
{
	return srtTransformCtrls.length();
}

void wxArraySRTTransformCtrl::setValue(int idx, const SRTTransform &value_)
{
	values[idx] = value_;
	srtTransformCtrls[idx]->setValue(value_);
}

SRTTransform wxArraySRTTransformCtrl::getValue(int idx) const
{
	return srtTransformCtrls[idx]->getValue();
}

void wxArraySRTTransformCtrl::createElementsUI()
{
	wxWindow *contentPanel = this->GetPane();

	srtTransformCtrls.resize(values.length());
	for(int i=0; i<srtTransformCtrls.length(); i++)
	{
		wxString str;
		str.Printf("Element%d", i);
		srtTransformCtrls[i] = new wxSRTTransformCtrl(contentPanel, wxID_ANY, 
			                                          str,
													  values[i],
													  this->GetTopLevelWindow(),
			                                          wxDefaultPosition, wxDefaultSize);
		flexSizer->Add(srtTransformCtrls[i], 1, wxBOTTOM | wxEXPAND, 4);

		srtTransformCtrls[i]->Connect(wxEVT_COMMAND_SRTTRANSFORM_CTRL_VALUE_CHANGED, wxSRTTransformCtrlEventHandler(wxArraySRTTransformCtrl::onSRTTransformValueChanged)		, 0, this);
	}
}

void wxArraySRTTransformCtrl::destroyElementsUI()
{
	for(int i=0; i<srtTransformCtrls.length(); i++)
	{
		delete srtTransformCtrls[i];
	}
	srtTransformCtrls.destroy();
}

void wxArraySRTTransformCtrl::resizeElementsUI(int newLength)
{
	int oldLength = values.length();
	if(newLength==oldLength)
		return;

	SRTTransform lastValue(Vector3::ONE, Vector3::ZERO, Vector3::ZERO);
	if(newLength>oldLength && values.length()!=0)
		lastValue = values.back();

	values.resize(newLength);
	for(int i=oldLength; i<values.length(); i++)
		values[i] = lastValue;

	destroyElementsUI();
	createElementsUI();

	wxArraySRTTransformCtrlEvent event(wxEVT_COMMAND_ARRAY_SRTTRANSFORM_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(values);
	
	GetEventHandler()->ProcessEvent( event );
}

void wxArraySRTTransformCtrl::onLengthChanged(wxArrayLengthCtrlEvent &evt)
{
	int newLength = evt.GetLength();
	
	resizeElementsUI(newLength);

	this->OnStateChange(this->GetBestSize());
}

void wxArraySRTTransformCtrl::onSRTTransformValueChanged(wxSRTTransformCtrlEvent &evt)
{
	int idx = 0;
	for(int i=0; i<srtTransformCtrls.length(); i++)
	{
		if(srtTransformCtrls[i]==evt.GetEventObject())
		{
			idx = i;
			break;
		}
	}

	values[idx] = evt.GetValue();

	wxArraySRTTransformCtrlEvent event(wxEVT_COMMAND_ARRAY_SRTTRANSFORM_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(GetLabel());
	event.SetValue(values);
	
	GetEventHandler()->ProcessEvent( evt );
}