#include "wxIVector4SpinnerCtrl.h"

////////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC_CLASS( wxIVector4SpinnerCtrlEvent, wxNotifyEvent )
DEFINE_EVENT_TYPE( wxEVT_COMMAND_IVECTOR4_SPINNER_CTRL_VALUE_CHANGED )

////////////////////////////////////////////////////////////////////////////////////////
wxIVector4SpinnerCtrl::wxIVector4SpinnerCtrl(wxWindow *parent_, wxWindowID id_,
										     const char *label_, bool collapsable_,
										     const IVector4 &value_, const IVector4 &minValue_, const IVector4 &maxValue_,
										     wxWindow *topLevelWindow_,
										     const wxPoint &pos_, const wxSize &size_,
										     long style_)
: wxPanel(parent_, id_, pos_, size_, style_)
, label(label_)
, intSpinners(3)
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
		for(int i=0; i<intSpinners.length(); i++)
		{
			const char *labels[] = { "X", "Y", "Z", "W" };

			intSpinners[i] = new wxIntSpinnerCtrl(subPanel, wxID_ANY, labels[i],
												  value_[i], minValue_[i], maxValue_[i], 
												  128, 120,
												  wxDefaultPosition, wxDefaultSize);
		}

		wxBoxSizer *hBox				= new wxBoxSizer(wxHORIZONTAL);
		wxBoxSizer *vBox				= new wxBoxSizer(wxVERTICAL);
		subPanel->SetSizer(hBox);
			hBox->Add(COLLAPSE_BUTTON_SIZE*1.5*2, COLLAPSE_BUTTON_SIZE, 0);
			hBox->Add(vBox, 1, wxEXPAND);
				for(int i=0; i<intSpinners.length(); i++)
				{
					vBox->Add(intSpinners[i], 1, wxEXPAND | wxBOTTOM, 4);
					
					intSpinners[i]->Connect(wxEVT_COMMAND_INT_SPINNER_CTRL_VALUE_CHANGED, wxIntSpinnerCtrlEventHandler(wxIVector4SpinnerCtrl::onIntValueChanged)		, 0, this);
				}
	}
	else
	{
		this->SetBackgroundColour(parent_->GetBackgroundColour());
		this->SetForegroundColour(parent_->GetForegroundColour());

		for(int i=0; i<intSpinners.length(); i++)
		{
			const char *labels[] = { "X", "Y", "Z", "W" };

			intSpinners[i] = new wxIntSpinnerCtrl(this, wxID_ANY, labels[i], 
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
					for(int i=0; i<intSpinners.length(); i++)
					{
						hBox1->Add(COLLAPSE_BUTTON_SIZE*1.5, COLLAPSE_BUTTON_SIZE, 0);
						hBox1->Add(intSpinners[i], 1, wxEXPAND);
						intSpinners[i]->Connect(wxEVT_COMMAND_INT_SPINNER_CTRL_VALUE_CHANGED, wxIntSpinnerCtrlEventHandler(wxIVector4SpinnerCtrl::onIntValueChanged)		, 0, this);
					}
	}
}

void wxIVector4SpinnerCtrl::setMinValue(const IVector4 &value_)
{
	for(int i=0; i<intSpinners.length(); i++)
		intSpinners[i]->setMinValue(value_[i]);
}

IVector4 wxIVector4SpinnerCtrl::getMinValue() const
{
	IVector4 rval;

	for(int i=0; i<intSpinners.length(); i++)
		rval[i] = intSpinners[i]->getMinValue();

	return rval;
}

void wxIVector4SpinnerCtrl::setMaxValue(const IVector4 &value_)
{
	for(int i=0; i<intSpinners.length(); i++)
		intSpinners[i]->setMaxValue(value_[i]);
}

IVector4 wxIVector4SpinnerCtrl::getMaxValue() const
{
	IVector4 rval;

	for(int i=0; i<intSpinners.length(); i++)
		rval[i] = intSpinners[i]->getMaxValue();

	return rval;
}

void wxIVector4SpinnerCtrl::setValue(const IVector4 &value_)
{
	for(int i=0; i<intSpinners.length(); i++)
		intSpinners[i]->setValue(value_[i]);
}

IVector4 wxIVector4SpinnerCtrl::getValue() const
{
	IVector4 rval;

	for(int i=0; i<intSpinners.length(); i++)
		rval[i] = intSpinners[i]->getValue();

	return rval;
}

void wxIVector4SpinnerCtrl::onIntValueChanged(wxIntSpinnerCtrlEvent &evt)
{
	wxIVector4SpinnerCtrlEvent event(wxEVT_COMMAND_IVECTOR4_SPINNER_CTRL_VALUE_CHANGED, GetId());
	event.SetEventObject(this);
	event.SetName(label);
	event.SetValue(getValue());

	GetEventHandler()->ProcessEvent( event );
}