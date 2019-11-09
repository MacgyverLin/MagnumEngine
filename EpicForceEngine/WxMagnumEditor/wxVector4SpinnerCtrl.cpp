#include "wxVector4SpinnerCtrl.h"

////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC_CLASS( wxVector4SpinnerCtrlEvent, wxNotifyEvent )
DEFINE_EVENT_TYPE( wxEVT_COMMAND_VECTOR4_SPINNER_CTRL_VALUE_CHANGED )

////////////////////////////////////////////////////////////////////////////////////////
wxVector4SpinnerCtrl::wxVector4SpinnerCtrl(wxWindow *parent_, wxWindowID id_,
										   const char *label_, bool collapsable_,
										   const Vector4 &value_, const Vector4 &minValue_, const Vector4 &maxValue_,
										   wxWindow *topLevelWindow_,
										   const wxPoint &pos_, const wxSize &size_,
										   long style_)
: wxPanel(parent_, id_, pos_, size_, style_)
, label(label_)
, floatSpinners(4)
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
					
					floatSpinners[i]->Connect(wxEVT_COMMAND_FLOAT_SPINNER_CTRL_VALUE_CHANGED, wxFloatSpinnerCtrlEventHandler(wxVector4SpinnerCtrl::onFloatValueChanged)		, 0, this);
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
						floatSpinners[i]->Connect(wxEVT_COMMAND_FLOAT_SPINNER_CTRL_VALUE_CHANGED, wxFloatSpinnerCtrlEventHandler(wxVector4SpinnerCtrl::onFloatValueChanged)		, 0, this);
					}
	}
}

void wxVector4SpinnerCtrl::setMinValue(const Vector4 &value_)
{
	for(int i=0; i<floatSpinners.length(); i++)
		floatSpinners[i]->setMinValue(value_[i]);
}

Vector4 wxVector4SpinnerCtrl::getMinValue() const
{
	Vector4 rval;

	for(int i=0; i<floatSpinners.length(); i++)
		rval[i] = floatSpinners[i]->getMinValue();

	return rval;
}

void wxVector4SpinnerCtrl::setMaxValue(const Vector4 &value_)
{
	for(int i=0; i<floatSpinners.length(); i++)
		floatSpinners[i]->setMaxValue(value_[i]);
}

Vector4 wxVector4SpinnerCtrl::getMaxValue() const
{
	Vector4 rval;

	for(int i=0; i<floatSpinners.length(); i++)
		rval[i] = floatSpinners[i]->getMaxValue();

	return rval;
}

void wxVector4SpinnerCtrl::setValue(const Vector4 &value_)
{
	for(int i=0; i<floatSpinners.length(); i++)
		floatSpinners[i]->setValue(value_[i]);
}

Vector4 wxVector4SpinnerCtrl::getValue() const
{
	Vector4 rval;

	for(int i=0; i<floatSpinners.length(); i++)
		rval[i] = floatSpinners[i]->getValue();

	return rval;
}

void wxVector4SpinnerCtrl::onFloatValueChanged(wxFloatSpinnerCtrlEvent &evt)
{
	wxVector4SpinnerCtrlEvent event(wxEVT_COMMAND_VECTOR4_SPINNER_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(label);
	event.SetValue(getValue());

	GetEventHandler()->ProcessEvent( event );
}