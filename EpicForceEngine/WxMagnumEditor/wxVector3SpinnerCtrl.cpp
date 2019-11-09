#include "wxVector3SpinnerCtrl.h"

////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC_CLASS( wxVector3SpinnerCtrlEvent, wxNotifyEvent )
DEFINE_EVENT_TYPE( wxEVT_COMMAND_VECTOR3_SPINNER_CTRL_VALUE_CHANGED )

////////////////////////////////////////////////////////////////////////////////////////
wxVector3SpinnerCtrl::wxVector3SpinnerCtrl(wxWindow *parent_, wxWindowID id_,
										   const char *label_, bool collapsable_,
										   const Vector3 &value_, const Vector3 &minValue_, const Vector3 &maxValue_,
										   wxWindow *topLevelWindow_,
										   const wxPoint &pos_, const wxSize &size_,
										   long style_)
: wxPanel(parent_, id_, pos_, size_, style_)
, label(label_)
, floatSpinners(3)
{
	if(collapsable_)
	{
		this->SetBackgroundColour(parent_->GetBackgroundColour());
		this->SetForegroundColour(parent_->GetForegroundColour());

		wxCollapsePanelCtrl *collapsePanel	=  new wxCollapsePanelCtrl(this, id_, label_, topLevelWindow_, pos_, size_, style_);
		wxBoxSizer *vBox1 = new wxBoxSizer(wxVERTICAL);
		this->SetSizer(vBox1);
			vBox1->Add(collapsePanel, 1, wxEXPAND);

		wxWindow *subPanel				= collapsePanel->GetPane();
		for(int i=0; i<floatSpinners.length(); i++)
		{
			const char *labels[] = { "X", "Y", "Z", "W" };

			floatSpinners[i] = new wxFloatSpinnerCtrl(subPanel, wxID_ANY, labels[i],
													  value_[i], minValue_[i], maxValue_[i], 
													  128, 120,
													  wxDefaultPosition, wxDefaultSize);
		}

		wxBoxSizer *hBox				= new wxBoxSizer(wxHORIZONTAL);
		wxBoxSizer *vBox				= new wxBoxSizer(wxVERTICAL);
		subPanel->SetSizer(hBox);
			hBox->Add(COLLAPSE_BUTTON_SIZE*1.5*2, COLLAPSE_BUTTON_SIZE, 0);
			hBox->Add(vBox, 1, wxEXPAND);
				for(int i=0; i<floatSpinners.length(); i++)
				{
					vBox->Add(floatSpinners[i], 1, wxEXPAND | wxBOTTOM, 4);
					
					floatSpinners[i]->Connect(wxEVT_COMMAND_FLOAT_SPINNER_CTRL_VALUE_CHANGED, wxFloatSpinnerCtrlEventHandler(wxVector3SpinnerCtrl::onFloatValueChanged)		, 0, this);
				}
	}
	else
	{
		this->SetBackgroundColour(parent_->GetBackgroundColour());
		this->SetForegroundColour(parent_->GetForegroundColour());

		for(int i=0; i<floatSpinners.length(); i++)
		{
			const char *labels[] = { "X", "Y", "Z", "W" };

			floatSpinners[i] = new wxFloatSpinnerCtrl(this, wxID_ANY, labels[i], 
													  value_[i], minValue_[i], maxValue_[i], 
													  32, 64,
													  wxDefaultPosition, wxDefaultSize);
		}

		wxBoxSizer *hBox = new wxBoxSizer(wxHORIZONTAL);
		wxBoxSizer *vBox = new wxBoxSizer(wxVERTICAL);
		wxBoxSizer *hBox1 = new wxBoxSizer(wxHORIZONTAL);
		this->SetSizer(hBox);
			//hBox->Add(COLLAPSE_BUTTON_SIZE*1.5, COLLAPSE_BUTTON_SIZE, 0);
			hBox->Add(vBox, 1, wxEXPAND);
				vBox->Add(new wxStaticText(this, wxID_ANY, label_), 1, wxEXPAND | wxBOTTOM, 4);
				vBox->Add(hBox1, 1, wxEXPAND | wxBOTTOM, 4);
					for(int i=0; i<floatSpinners.length(); i++)
					{
						hBox1->Add(COLLAPSE_BUTTON_SIZE*1.5, COLLAPSE_BUTTON_SIZE, 0);
						hBox1->Add(floatSpinners[i], 1, wxEXPAND);
						floatSpinners[i]->Connect(wxEVT_COMMAND_FLOAT_SPINNER_CTRL_VALUE_CHANGED, wxFloatSpinnerCtrlEventHandler(wxVector3SpinnerCtrl::onFloatValueChanged)		, 0, this);
					}
	}
}

void wxVector3SpinnerCtrl::setMinValue(const Vector3 &value_)
{
	for(int i=0; i<floatSpinners.length(); i++)
		floatSpinners[i]->setMinValue(value_[i]);
}

Vector3 wxVector3SpinnerCtrl::getMinValue() const
{
	Vector3 rval;

	for(int i=0; i<floatSpinners.length(); i++)
		rval[i] = floatSpinners[i]->getMinValue();

	return rval;
}

void wxVector3SpinnerCtrl::setMaxValue(const Vector3 &value_)
{
	for(int i=0; i<floatSpinners.length(); i++)
		floatSpinners[i]->setMaxValue(value_[i]);
}

Vector3 wxVector3SpinnerCtrl::getMaxValue() const
{
	Vector3 rval;

	for(int i=0; i<floatSpinners.length(); i++)
		rval[i] = floatSpinners[i]->getMaxValue();

	return rval;
}

void wxVector3SpinnerCtrl::setValue(const Vector3 &value_)
{
	for(int i=0; i<floatSpinners.length(); i++)
		floatSpinners[i]->setValue(value_[i]);
}

Vector3 wxVector3SpinnerCtrl::getValue() const
{
	Vector3 rval;

	for(int i=0; i<floatSpinners.length(); i++)
		rval[i] = floatSpinners[i]->getValue();

	return rval;
}

void wxVector3SpinnerCtrl::onFloatValueChanged(wxFloatSpinnerCtrlEvent &evt)
{
	wxVector3SpinnerCtrlEvent event(wxEVT_COMMAND_VECTOR3_SPINNER_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(label);
	event.SetValue(getValue());

	GetEventHandler()->ProcessEvent( event );
}