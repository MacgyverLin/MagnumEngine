#ifndef _wxStringCtrl_h_
#define _wxStringCtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"
#include "EString.h"
using namespace Magnum;

class wxStringCtrlEvent : public wxNotifyEvent
{
public:
	wxStringCtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxStringCtrlEvent(const wxStringCtrlEvent& event)
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

	wxEvent* Clone() const {return new wxStringCtrlEvent(*this); }
protected:
private:
	wxString name;

	String value;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxStringCtrlEvent)
};

typedef void (wxEvtHandler::*wxStringCtrlEventFunction)(wxStringCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_STRING_CTRL_VALUE_CHANGED, 1 )
END_DECLARE_EVENT_TYPES()

#define wxStringCtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxStringCtrlEventFunction, &func)

#define wx__DECLARE_STRING_CTRL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_STRING_CTRL_ ## evt, id, wxStringCtrlEventHandler(fn))	

#define EVT_STRING_CTRL_VALUE_CHANGED(id, fn) wx__DECLARE_STRING_CTRL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxStringCtrl : public wxPanel
{
public:
	wxStringCtrl(wxWindow *parent_, wxWindowID id_,
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
	void fireEvent();
public:
protected:
private:
	void OnTextEntered(wxCommandEvent &evt);
	//void OnTextUpdated(wxCommandEvent &evt);
public:
protected:
private:
	String				value;
	wxStaticText		*staticText;
	wxTextCtrl			*textCtrl;
};

#endif