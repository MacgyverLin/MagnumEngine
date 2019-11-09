#ifndef _wxIVector2SpinnerCtrl_h_
#define _wxIVector2SpinnerCtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"
#include "wxIntSpinnerCtrl.h"
#include "wxCollapsePanelCtrl.h"
#include "IVector2.h"
using namespace Magnum;

class wxIVector2SpinnerCtrlEvent : public wxNotifyEvent
{
public:
	wxIVector2SpinnerCtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxIVector2SpinnerCtrlEvent(const wxIVector2SpinnerCtrlEvent& event)
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

	const IVector2 &GetValue() const 
	{ 
		return value; 
	};

	void SetValue(const IVector2 &value_) 
	{
		value = value_;
	}

	wxEvent* Clone() const {return new wxIVector2SpinnerCtrlEvent(*this); }
protected:
private:
	wxString name;

	IVector2 value;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxIVector2SpinnerCtrlEvent)
};

typedef void (wxEvtHandler::*wxIVector2SpinnerCtrlEventFunction)(wxIVector2SpinnerCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_IVECTOR2_SPINNER_CTRL_VALUE_CHANGED, 1 )
END_DECLARE_EVENT_TYPES()

#define wxIVector2SpinnerCtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxIVector2SpinnerCtrlEventFunction, &func)

#define wx__DECLARE_IVECTOR2_SPINNER_CTRL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_IVECTOR2_SPINNER_CTRL_ ## evt, id, wxIVector2SpinnerCtrlEventHandler(fn))	

#define EVT_IVECTOR2_SPINNER_CTRL_VALUE_CHANGED(id, fn) wx__DECLARE_IVECTOR2_SPINNER_CTRL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxIVector2SpinnerCtrl : public wxPanel
{
public:
	wxIVector2SpinnerCtrl(wxWindow *parent_, wxWindowID id_,
						  const char *caption_, bool collapsable_,
						  const IVector2 &value_, const IVector2 &minValue_, const IVector2 &maxValue_,
						  wxWindow *topLevelWindow_ = 0,
						  const wxPoint& pos_ = wxDefaultPosition,
						  const wxSize& size_ = wxDefaultSize,
						  long style_ = wxCP_DEFAULT_STYLE);

	void setMinValue(const IVector2 &value_);
	IVector2 getMinValue() const;

	void setMaxValue(const IVector2 &value_);
	IVector2 getMaxValue() const;

	void setValue(const IVector2 &value_);
	IVector2 getValue() const;
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