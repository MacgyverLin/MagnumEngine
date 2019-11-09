#ifndef _wxDoubleSpinnerCtrl_h_
#define _wxDoubleSpinnerCtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"

class wxDoubleSpinnerCtrlEvent : public wxNotifyEvent
{
public:
	wxDoubleSpinnerCtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxDoubleSpinnerCtrlEvent(const wxDoubleSpinnerCtrlEvent& event)
	: wxNotifyEvent(event)
	, name(event.name)
	, value(event.value)
	{
	}

	const wxString &GetName() const 
	{ 
		return name; 
	}

	void SetName(const wxString &name_) 
	{
		name = name_;
	}

	double GetValue() const 
	{ 
		return value; 
	};

	void SetValue(double value_) 
	{
		value = value_;
	}

	wxEvent* Clone() const {return new wxDoubleSpinnerCtrlEvent(*this); }
protected:
private:
	wxString name;

	double value;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxDoubleSpinnerCtrlEvent)
};

typedef void (wxEvtHandler::*wxDoubleSpinnerCtrlEventFunction)(wxDoubleSpinnerCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_DOUBLE_SPINNER_CTRL_VALUE_CHANGED, 1)
END_DECLARE_EVENT_TYPES()

#define wxDoubleSpinnerCtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxDoubleSpinnerCtrlEventFunction, &func)

#define wx__DECLARE_DOUBLE_SPINNER_CTRL_EVT(evt, id, fn) \
	wx__DECLARE_EVT1(wxEVT_COMMAND_DOUBLE_SPINNER_CTRL_ ## evt, id, wxDoubleSpinnerCtrlEventHandler(fn))	

#define EVT_DOUBLE_SPINNER_CTRL_VALUE_CHANGED(id, fn) wx__DECLARE_DOUBLE_SPINNER_CTRL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxDoubleSpinnerCtrl : public wxPanel
{
public:
	wxDoubleSpinnerCtrl(wxWindow *parent_, wxWindowID id_,
					    const char *label_,
					    double value_, double minValue_, double maxValue_,
						int labelWidth_ = 128, int textBoxWidth_ = 120,
					    const wxPoint& pos_ = wxDefaultPosition,
					    const wxSize& size_ = wxDefaultSize,
					    long style_ = wxBORDER_NONE);

	wxString GetLabel() const
	{
		return staticText->GetLabel();
	}

	void setMinValue(double value_);
	double getMinValue() const;

	void setMaxValue(double value_);
	double getMaxValue() const;

	void setValue(double value_);
	double getValue() const;
protected:
private:
	void calculateUnitPerPixel();
	float updateMouse();
	float getIncrement(float delta);
	void updateValue(float oldvalue, float delta);
	void updateUIValue();

	void fireEvent();

	wxString getValueText();
public:
protected:
private:
	void onMouseDown(wxMouseEvent &evt);
	void onMouseUp(wxMouseEvent &evt);
	void onMove(wxMouseEvent &evt);
	void onMouseCaptureLost(wxMouseCaptureLostEvent &evt);
	void onTextEntered(wxCommandEvent &evt);
public:
protected:
private:
	double				minValue, maxValue, value;
	float				residue;
	float				unitPerPixel;
	bool				dragging;

	wxPoint				mouseDownPosition;
	wxPoint				oldPosition;
	
	wxStaticText		*staticText;
	wxTextCtrl			*textCtrl;
};

#endif