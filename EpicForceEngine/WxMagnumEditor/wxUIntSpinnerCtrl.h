#ifndef _wxUIntSpinnerCtrl_h_
#define _wxUIntSpinnerCtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"

class wxUIntSpinnerCtrlEvent : public wxNotifyEvent
{
public:
	wxUIntSpinnerCtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxUIntSpinnerCtrlEvent(const wxUIntSpinnerCtrlEvent& event)
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

	unsigned int GetValue() const 
	{ 
		return value; 
	};

	void SetValue(unsigned int value_) 
	{
		value = value_;
	}

	wxEvent* Clone() const {return new wxUIntSpinnerCtrlEvent(*this); }
protected:
private:
	wxString name;

	unsigned int value;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxUIntSpinnerCtrlEvent)
};

typedef void (wxEvtHandler::*wxUIntSpinnerCtrlEventFunction)(wxUIntSpinnerCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_UINT_SPINNER_CTRL_VALUE_CHANGED, 1)
END_DECLARE_EVENT_TYPES()

#define wxUIntSpinnerCtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxUIntSpinnerCtrlEventFunction, &func)

#define wx__DECLARE_UINT_SPINNER_CTRL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_INT_SPINNER_CTRL_ ## evt, id, wxUIntSpinnerCtrlEventHandler(fn))	

#define EVT_UINT_SPINNER_CTRL_VALUE_CHANGED(id, fn) wx__DECLARE_UINT_SPINNER_CTRL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxUIntSpinnerCtrl : public wxPanel
{
public:
	wxUIntSpinnerCtrl(wxWindow *parent_, wxWindowID id_,
					 const char *label_,
					 unsigned int value_, unsigned int minValue_, unsigned int maxValue_,
					 int labelWidth_ = 128, int textBoxWidth_ = 120,
					 const wxPoint& pos_ = wxDefaultPosition,
					 const wxSize& size_ = wxDefaultSize,
					 long style_ = wxBORDER_NONE);

	wxString GetLabel() const
	{
		return staticText->GetLabel();
	}

	void setMinValue(unsigned int value_);
	unsigned int getMinValue() const;

	void setMaxValue(unsigned int value_);
	unsigned int getMaxValue() const;

	void setValue(unsigned int value_);
	unsigned int getValue() const;
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
	double				value, minValue, maxValue;
	float				residue;
	float				unitPerPixel;
	bool				dragging;

	wxPoint				mouseDownPosition;
	wxPoint				oldPosition;
	
	wxStaticText		*staticText;
	wxTextCtrl			*textCtrl;
};

#endif