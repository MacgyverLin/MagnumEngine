#ifndef _wxLabelCtrl_h_
#define _wxLabelCtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"
#include "EString.h"
using namespace Magnum;

class wxLabelCtrlEvent : public wxNotifyEvent
{
public:
	wxLabelCtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxLabelCtrlEvent(const wxLabelCtrlEvent& event)
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

	const String &GetValue() const 
	{ 
		return value; 
	};

	void SetValue(const String &value_) 
	{
		value = value_;
	}

	wxEvent* Clone() const {return new wxLabelCtrlEvent(*this); }
protected:
private:
	wxString name;

	String value;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxLabelCtrlEvent)
};

typedef void (wxEvtHandler::*wxLabelCtrlEventFunction)(wxLabelCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_LABEL_CTRL_VALUE_CHANGED, 1 )
END_DECLARE_EVENT_TYPES()

#define wxLabelCtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxLabelCtrlEventFunction, &func)

#define wx__DECLARE_LABEL_CTRL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_LABEL_CTRL_ ## evt, id, wxLabelCtrlEventHandler(fn))	

#define EVT_LABEL_CTRL_VALUE_CHANGED(id, fn) wx__DECLARE_LABEL_CTRL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxLabelCtrl : public wxPanel
{
public:
	wxLabelCtrl(wxWindow *parent_, wxWindowID id_,
				const char *label_, const String &value_, 
				const wxPoint& pos_ = wxDefaultPosition,
				const wxSize& size_ = wxDefaultSize,
				long style_ = wxBORDER_NONE);

	wxString GetLabel() const
	{
		return staticText->GetLabel();
	}

	void setValue(const String &value_);
	String getValue() const;
protected:
private:

public:
protected:
private:

public:
protected:
private:
	String				value;
	wxStaticText		*staticText;
	wxStaticText		*textCtrl;
};

#endif