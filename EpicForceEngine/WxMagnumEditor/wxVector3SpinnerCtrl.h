#ifndef _wxVector3SpinnerCtrl_h_
#define _wxVector3SpinnerCtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"
#include "wxFloatSpinnerCtrl.h"
#include "wxCollapsePanelCtrl.h"
#include "Vector3.h"
using namespace Magnum;

class wxVector3SpinnerCtrlEvent : public wxNotifyEvent
{
public:
	wxVector3SpinnerCtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxVector3SpinnerCtrlEvent(const wxVector3SpinnerCtrlEvent& event)
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

	const Vector3 &GetValue() const 
	{ 
		return value; 
	};

	void SetValue(const Vector3 &value_) 
	{
		value = value_;
	}

	wxEvent* Clone() const {return new wxVector3SpinnerCtrlEvent(*this); }
protected:
private:
	wxString name;

	Vector3 value;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxVector3SpinnerCtrlEvent)
};

typedef void (wxEvtHandler::*wxVector3SpinnerCtrlEventFunction)(wxVector3SpinnerCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_VECTOR3_SPINNER_CTRL_VALUE_CHANGED, 1 )
END_DECLARE_EVENT_TYPES()

#define wxVector3SpinnerCtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxVector3SpinnerCtrlEventFunction, &func)

#define wx__DECLARE_VECTOR3_SPINNER_CTRL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_VECTOR3_SPINNER_CTRL_ ## evt, id, wxVector3SpinnerCtrlEventHandler(fn))	

#define EVT_VECTOR3_SPINNER_CTRL_VALUE_CHANGED(id, fn) wx__DECLARE_VECTOR3_SPINNER_CTRL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxVector3SpinnerCtrl : public wxPanel
{
public:
	wxVector3SpinnerCtrl(wxWindow *parent_, wxWindowID id_,
						 const char *caption_, bool collapsable_,
						 const Vector3 &value_, const Vector3 &minValue_, const Vector3 &maxValue_,
						 wxWindow *topLevelWindow_ = 0,
						 const wxPoint& pos_ = wxDefaultPosition,
						 const wxSize& size_ = wxDefaultSize,
						 long style_ = wxCP_DEFAULT_STYLE);

	void setMinValue(const Vector3 &value_);
	Vector3 getMinValue() const;

	void setMaxValue(const Vector3 &value_);
	Vector3 getMaxValue() const;

	void setValue(const Vector3 &value_);
	Vector3 getValue() const;
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