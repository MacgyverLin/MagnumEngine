#ifndef _wxBoolCtrl_h_
#define _wxBoolCtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"
#include "ColorRGBA.h"
using namespace Magnum;

class wxBoolCtrlEvent : public wxNotifyEvent
{
public:
	wxBoolCtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxBoolCtrlEvent(const wxBoolCtrlEvent& event)
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

	const bool GetValue() const 
	{ 
		return value; 
	};

	void SetValue(bool value_) 
	{
		value = value_;
	}

	wxEvent* Clone() const {return new wxBoolCtrlEvent(*this); }
protected:
private:
	wxString name;

	bool value;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxBoolCtrlEvent)
};

typedef void (wxEvtHandler::*wxBoolCtrlEventFunction)(wxBoolCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_BOOL_CTRL_VALUE_CHANGED, 1 )
END_DECLARE_EVENT_TYPES()

#define wxBoolCtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxBoolCtrlEventFunction, &func)

#define wx__DECLARE_BOOL_CTRL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_BOOL_CTRL_ ## evt, id, wxBoolCtrlEventHandler(fn))	

#define EVT_BOOL_CTRL_VALUE_CHANGED(id, fn) wx__DECLARE_BOOL_CTRL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxBoolCtrl : public wxPanel
{
public:
	wxBoolCtrl(wxWindow *parent_, wxWindowID id_,
			   const char *label_, 
			   const bool &value_, 
			   const wxPoint& pos_ = wxDefaultPosition,
			   const wxSize& size_ = wxDefaultSize,
			   long style_ = wxBORDER_NONE);

	wxString GetLabel() const
	{
		return staticText->GetLabel();
	}

	void setValue(const bool &value_);
	bool getValue() const;
protected:
private:
	void fireEvent();
public:
protected:
private:
	void OnChecked(wxCommandEvent &evt);
public:
protected:
private:
	bool				value;
	wxStaticText		*staticText;
	wxCheckBox			*checkBox;
};

#endif