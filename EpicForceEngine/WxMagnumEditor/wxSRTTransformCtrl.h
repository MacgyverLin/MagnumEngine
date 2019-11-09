#ifndef _wxSRTTransformCtrl_h_
#define _wxSRTTransformCtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"
#include "wxVector3SpinnerCtrl.h"
#include "wxCollapsePanelCtrl.h"
#include "SRTTransform.h"
using namespace Magnum;

class wxSRTTransformCtrlEvent : public wxNotifyEvent
{
public:
	wxSRTTransformCtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxSRTTransformCtrlEvent(const wxSRTTransformCtrlEvent& event)
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

	const SRTTransform &GetValue() const 
	{ 
		return value; 
	};

	void SetValue(const SRTTransform &value_) 
	{
		value = value_;
	}

	wxEvent* Clone() const {return new wxSRTTransformCtrlEvent(*this); }
protected:
private:
	wxString name;

	SRTTransform value;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxSRTTransformCtrlEvent)
};

typedef void (wxEvtHandler::*wxSRTTransformCtrlEventFunction)(wxSRTTransformCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_SRTTRANSFORM_CTRL_VALUE_CHANGED, 1 )
END_DECLARE_EVENT_TYPES()

#define wxSRTTransformCtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxSRTTransformCtrlEventFunction, &func)

#define wx__DECLARE_SRTTRANSFORM_CTRL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_SRTTRANSFORM_CTRL_ ## evt, id, wxSRTTransformCtrlEventHandler(fn))	

#define EVT_SRTTRANSFORM_CTRL_VALUE_CHANGED(id, fn) wx__DECLARE_SRTTRANSFORM_CTRL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxSRTTransformCtrl : public wxCollapsePanelCtrl
{
public:
	wxSRTTransformCtrl(wxWindow *parent_, wxWindowID id_,
					   const char *caption_, 
					   const SRTTransform &value_,
					   wxWindow *topLevelWindow_ = 0,
					   const wxPoint& pos_ = wxDefaultPosition,
					   const wxSize& size_ = wxDefaultSize,
					   long style_ = wxCP_DEFAULT_STYLE);

	void setValue(const SRTTransform &value_);
	SRTTransform getValue() const;
protected:
private:


public:
protected:
private:
	void onPositionValueChanged(wxVector3SpinnerCtrlEvent &evt);
	void onRotationValueChanged(wxVector3SpinnerCtrlEvent &evt);
	void onScaleValueChanged(wxVector3SpinnerCtrlEvent &evt);
public:
protected:
private:
	wxBoxSizer						*hBox;
	wxFlexGridSizer					*flexSizer;

	Array<wxVector3SpinnerCtrl *> vector3Spinners;
};

#endif