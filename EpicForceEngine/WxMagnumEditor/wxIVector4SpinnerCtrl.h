#ifndef _wxIVector4SpinnerCtrl_h_
#define _wxIVector4SpinnerCtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"
#include "wxIntSpinnerCtrl.h"
#include "wxCollapsePanelCtrl.h"
#include "IVector4.h"
using namespace Magnum;

class wxIVector4SpinnerCtrlEvent : public wxNotifyEvent
{
public:
	wxIVector4SpinnerCtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxIVector4SpinnerCtrlEvent(const wxIVector4SpinnerCtrlEvent& event)
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

	const IVector4 &GetValue() const 
	{ 
		return value; 
	};

	void SetValue(const IVector4 &value_) 
	{
		value = value_;
	}

	wxEvent* Clone() const {return new wxIVector4SpinnerCtrlEvent(*this); }
protected:
private:
	wxString name;

	IVector4 value;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxIVector4SpinnerCtrlEvent)
};

typedef void (wxEvtHandler::*wxIVector4SpinnerCtrlEventFunction)(wxIVector4SpinnerCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_IVECTOR4_SPINNER_CTRL_VALUE_CHANGED, 1 )
END_DECLARE_EVENT_TYPES()

#define wxIVector4SpinnerCtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxIVector4SpinnerCtrlEventFunction, &func)

#define wx__DECLARE_IVECTOR4_SPINNER_CTRL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_IVECTOR4_SPINNER_CTRL_ ## evt, id, wxIVector4SpinnerCtrlEventHandler(fn))	

#define EVT_IVECTOR4_SPINNER_CTRL_VALUE_CHANGED(id, fn) wx__DECLARE_IVECTOR4_SPINNER_CTRL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxIVector4SpinnerCtrl : public wxPanel
{
public:
	wxIVector4SpinnerCtrl(wxWindow *parent_, wxWindowID id_,
						  const char *caption_, bool collapsable_,
						  const IVector4 &value_, const IVector4 &minValue_, const IVector4 &maxValue_,
						  wxWindow *topLevelWindow_ = 0,
						  const wxPoint& pos_ = wxDefaultPosition,
						  const wxSize& size_ = wxDefaultSize,
						  long style_ = wxCP_DEFAULT_STYLE);

	void setMinValue(const IVector4 &value_);
	IVector4 getMinValue() const;

	void setMaxValue(const IVector4 &value_);
	IVector4 getMaxValue() const;

	void setValue(const IVector4 &value_);
	IVector4 getValue() const;
protected:
private:


public:
protected:
private:
	void onIntValueChanged(wxIntSpinnerCtrlEvent &evt);
public:
protected:
private:
	wxString label;
	Array<wxIntSpinnerCtrl *> intSpinners;
};

#endif