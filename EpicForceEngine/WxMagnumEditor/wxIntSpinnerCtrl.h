#ifndef _wxIntSpinnerCtrl_h_
#define _wxIntSpinnerCtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"

class wxIntSpinnerCtrlEvent : public wxNotifyEvent
{
public:
	wxIntSpinnerCtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxIntSpinnerCtrlEvent(const wxIntSpinnerCtrlEvent& event)
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

	int GetValue() const 
	{ 
		return value; 
	};

	void SetValue(int value_) 
	{
		value = value_;
	}

	wxEvent* Clone() const {return new wxIntSpinnerCtrlEvent(*this); }
protected:
private:
	wxString name;

	int value;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxIntSpinnerCtrlEvent)
};

typedef void (wxEvtHandler::*wxIntSpinnerCtrlEventFunction)(wxIntSpinnerCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_INT_SPINNER_CTRL_VALUE_CHANGED, 1)
END_DECLARE_EVENT_TYPES()

#define wxIntSpinnerCtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxIntSpinnerCtrlEventFunction, &func)

#define wx__DECLARE_INT_SPINNER_CTRL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_INT_SPINNER_CTRL_ ## evt, id, wxIntSpinnerCtrlEventHandler(fn))	

#define EVT_INT_SPINNER_CTRL_VALUE_CHANGED(id, fn) wx__DECLARE_INT_SPINNER_CTRL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxIntSpinnerCtrl : public wxPanel
{
public:
	wxIntSpinnerCtrl(wxWindow *parent_, wxWindowID id_,
					 const char *label_,
					 int value_, int minValue_, int maxValue_,
					 int labelWidth_ = 128, int textBoxWidth_ = 120,
					 const wxPoint& pos_ = wxDefaultPosition,
					 const wxSize& size_ = wxDefaultSize,
					 long style_ = wxBORDER_NONE);

	wxString GetLabel() const
	{
		return staticText->GetLabel();
	}

	void setMinValue(int value_);
	int getMinValue() const;

	void setMaxValue(int value_);
	int getMaxValue() const;

	void setValue(int value_);
	int getValue() const;
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