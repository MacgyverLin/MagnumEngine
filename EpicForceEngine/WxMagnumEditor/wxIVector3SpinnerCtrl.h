#ifndef _wxIVector3SpinnerCtrl_h_
#define _wxIVector3SpinnerCtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"
#include "wxIntSpinnerCtrl.h"
#include "wxCollapsePanelCtrl.h"
#include "IVector3.h"
using namespace Magnum;

class wxIVector3SpinnerCtrlEvent : public wxNotifyEvent
{
public:
	wxIVector3SpinnerCtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxIVector3SpinnerCtrlEvent(const wxIVector3SpinnerCtrlEvent& event)
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

	const IVector3 &GetValue() const 
	{ 
		return value; 
	};

	void SetValue(const IVector3 &value_) 
	{
		value = value_;
	}

	wxEvent* Clone() const {return new wxIVector3SpinnerCtrlEvent(*this); }
protected:
private:
	wxString name;

	IVector3 value;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxIVector3SpinnerCtrlEvent)
};

typedef void (wxEvtHandler::*wxIVector3SpinnerCtrlEventFunction)(wxIVector3SpinnerCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_IVECTOR3_SPINNER_CTRL_VALUE_CHANGED, 1 )
END_DECLARE_EVENT_TYPES()

#define wxIVector3SpinnerCtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxIVector3SpinnerCtrlEventFunction, &func)

#define wx__DECLARE_IVECTOR3_SPINNER_CTRL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_IVECTOR3_SPINNER_CTRL_ ## evt, id, wxIVector3SpinnerCtrlEventHandler(fn))	

#define EVT_IVECTOR3_SPINNER_CTRL_VALUE_CHANGED(id, fn) wx__DECLARE_IVECTOR3_SPINNER_CTRL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxIVector3SpinnerCtrl : public wxPanel
{
public:
	wxIVector3SpinnerCtrl(wxWindow *parent_, wxWindowID id_,
						  const char *caption_, bool collapsable_,
						  const IVector3 &value_, const IVector3 &minValue_, const IVector3 &maxValue_,
						  wxWindow *topLevelWindow_ = 0,
						  const wxPoint& pos_ = wxDefaultPosition,
						  const wxSize& size_ = wxDefaultSize,
						  long style_ = wxCP_DEFAULT_STYLE);

	void setMinValue(const IVector3 &value_);
	IVector3 getMinValue() const;

	void setMaxValue(const IVector3 &value_);
	IVector3 getMaxValue() const;

	void setValue(const IVector3 &value_);
	IVector3 getValue() const;
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