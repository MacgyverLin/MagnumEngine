#ifndef _wxVector2SpinnerCtrl_h_
#define _wxVector2SpinnerCtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"
#include "wxFloatSpinnerCtrl.h"
#include "wxCollapsePanelCtrl.h"
#include "Vector2.h"
using namespace Magnum;

class wxVector2SpinnerCtrlEvent : public wxNotifyEvent
{
public:
	wxVector2SpinnerCtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxVector2SpinnerCtrlEvent(const wxVector2SpinnerCtrlEvent& event)
	: wxNotifyEvent(event)
	, name(event.name)
	, value(event.value)
	{
	}

	const wxString &GetName() const 
	{ 
		return name; 
	};

	void SetName(const wxString &name_) 
	{
		name = name_;
	}

	const Vector2 &GetValue() const 
	{ 
		return value; 
	};

	void SetValue(const Vector2 &value_) 
	{
		value = value_;
	}

	wxEvent* Clone() const {return new wxVector2SpinnerCtrlEvent(*this); }
protected:
private:
	wxString name;

	Vector2 value;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxVector2SpinnerCtrlEvent)
};

typedef void (wxEvtHandler::*wxVector2SpinnerCtrlEventFunction)(wxVector2SpinnerCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_VECTOR2_SPINNER_CTRL_VALUE_CHANGED, 1 )
END_DECLARE_EVENT_TYPES()

#define wxVector2SpinnerCtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxVector2SpinnerCtrlEventFunction, &func)

#define wx__DECLARE_VECTOR2_SPINNER_CTRL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_VECTOR2_SPINNER_CTRL_ ## evt, id, wxVector2SpinnerCtrlEventHandler(fn))	

#define EVT_VECTOR2_SPINNER_CTRL_VALUE_CHANGED(id, fn) wx__DECLARE_VECTOR2_SPINNER_CTRL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxVector2SpinnerCtrl : public wxPanel
{
public:
	wxVector2SpinnerCtrl(wxWindow *parent_, wxWindowID id_,
						 const char *caption_, bool collapsable_,
						 const Vector2 &value_, const Vector2 &minValue_, const Vector2 &maxValue_,
						 wxWindow *topLevelWindow_ = 0,
						 const wxPoint& pos_ = wxDefaultPosition,
						 const wxSize& size_ = wxDefaultSize,
						 long style_ = wxCP_DEFAULT_STYLE);

	void setMinValue(const Vector2 &value_);
	Vector2 getMinValue() const;

	void setMaxValue(const Vector2 &value_);
	Vector2 getMaxValue() const;

	void setValue(const Vector2 &value_);
	Vector2 getValue() const;
protected:
private:


public:
protected:
private:
	void onFloatValueChanged(wxFloatSpinnerCtrlEvent &evt);
public:
protected:
private:
	wxString label;
	Array<wxFloatSpinnerCtrl *> floatSpinners;
};

#endif