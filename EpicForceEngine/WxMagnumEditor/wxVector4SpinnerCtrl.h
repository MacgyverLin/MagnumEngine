#ifndef _wxVector4SpinnerCtrl_h_
#define _wxVector4SpinnerCtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"
#include "wxFloatSpinnerCtrl.h"
#include "wxCollapsePanelCtrl.h"
#include "Vector4.h"
using namespace Magnum;

class wxVector4SpinnerCtrlEvent : public wxNotifyEvent
{
public:
	wxVector4SpinnerCtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxVector4SpinnerCtrlEvent(const wxVector4SpinnerCtrlEvent& event)
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

	const Vector4 &GetValue() const 
	{ 
		return value; 
	};

	void SetValue(const Vector4 &value_) 
	{
		value = value_;
	}

	wxEvent* Clone() const {return new wxVector4SpinnerCtrlEvent(*this); }
protected:
private:
	wxString name;

	Vector4 value;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxVector4SpinnerCtrlEvent)
};

typedef void (wxEvtHandler::*wxVector4SpinnerCtrlEventFunction)(wxVector4SpinnerCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_VECTOR4_SPINNER_CTRL_VALUE_CHANGED, 1 )
END_DECLARE_EVENT_TYPES()

#define wxVector4SpinnerCtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxVector4SpinnerCtrlEventFunction, &func)

#define wx__DECLARE_VECTOR4_SPINNER_CTRL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_VECTOR4_SPINNER_CTRL_ ## evt, id, wxVector4SpinnerCtrlEventHandler(fn))	

#define EVT_VECTOR4_SPINNER_CTRL_VALUE_CHANGED(id, fn) wx__DECLARE_VECTOR4_SPINNER_CTRL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxVector4SpinnerCtrl : public wxPanel
{
public:
	wxVector4SpinnerCtrl(wxWindow *parent_, wxWindowID id_,
						 const char *caption_, bool collapsable_,
						 const Vector4 &value_, const Vector4 &minValue_, const Vector4 &maxValue_,
						 wxWindow *topLevelWindow_ = 0,
						 const wxPoint& pos_ = wxDefaultPosition,
						 const wxSize& size_ = wxDefaultSize,
						 long style_ = wxCP_DEFAULT_STYLE);

	void setMinValue(const Vector4 &value_);
	Vector4 getMinValue() const;

	void setMaxValue(const Vector4 &value_);
	Vector4 getMaxValue() const;

	void setValue(const Vector4 &value_);
	Vector4 getValue() const;
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