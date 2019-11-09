#ifndef _wxFloatSpinnerCtrl_h_
#define _wxFloatSpinnerCtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"

class wxFloatSpinnerCtrlEvent : public wxNotifyEvent
{
public:
	wxFloatSpinnerCtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxFloatSpinnerCtrlEvent(const wxFloatSpinnerCtrlEvent& event)
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

	float GetValue() const 
	{ 
		return value; 
	};

	void SetValue(float value_) 
	{
		value = value_;
	}

	wxEvent* Clone() const {return new wxFloatSpinnerCtrlEvent(*this); }
protected:
private:
	wxString name;

	float value;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxFloatSpinnerCtrlEvent)
};

typedef void (wxEvtHandler::*wxFloatSpinnerCtrlEventFunction)(wxFloatSpinnerCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_FLOAT_SPINNER_CTRL_VALUE_CHANGED, 1)
END_DECLARE_EVENT_TYPES()

#define wxFloatSpinnerCtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxFloatSpinnerCtrlEventFunction, &func)

#define wx__DECLARE_FLOAT_SPINNER_CTRL_EVT(evt, id, fn) \
	wx__DECLARE_EVT1(wxEVT_COMMAND_FLOAT_SPINNER_CTRL_ ## evt, id, wxFloatSpinnerCtrlEventHandler(fn))	

#define EVT_FLOAT_SPINNER_CTRL_VALUE_CHANGED(id, fn) wx__DECLARE_FLOAT_SPINNER_CTRL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxFloatSpinnerCtrl : public wxPanel
{
public:
	wxFloatSpinnerCtrl(wxWindow *parent_, wxWindowID id_,
					   const char *label_,
					   float value_, float minValue_, float maxValue_,
					   int labelWidth_ = 128, int textBoxWidth_ = 120,
					   const wxPoint& pos_ = wxDefaultPosition,
					   const wxSize& size_ = wxDefaultSize,
					   long style_ = wxBORDER_NONE);

	wxString GetLabel() const
	{
		return staticText->GetLabel();
	}

	void setMinValue(float value_);
	float getMinValue() const;

	void setMaxValue(float value_);
	float getMaxValue() const;

	void setValue(float value_);
	float getValue() const;
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
	float				minValue, maxValue, value;
	float				residue;
	float				unitPerPixel;
	bool				dragging;

	wxPoint				mouseDownPosition;
	wxPoint				oldPosition;
	
	wxStaticText		*staticText;
	wxTextCtrl			*textCtrl;
};

#endif