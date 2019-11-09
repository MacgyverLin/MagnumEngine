#ifndef _wxArrayLengthCtrl_h_
#define _wxArrayLengthCtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"

class wxArrayLengthCtrlEvent : public wxNotifyEvent
{
public:
	wxArrayLengthCtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxArrayLengthCtrlEvent(const wxArrayLengthCtrlEvent& event)
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

	unsigned int GetLength() const 
	{ 
		return value; 
	};

	void SetLength(const unsigned int &value_) 
	{
		value = value_;
	}

	wxEvent* Clone() const {return new wxArrayLengthCtrlEvent(*this); }
protected:
private:
	wxString name;

	unsigned int value;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxArrayLengthCtrlEvent)
};

typedef void (wxEvtHandler::*wxArrayLengthCtrlEventFunction)(wxArrayLengthCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_LENGTH_CTRL_VALUE_CHANGED, 1 )
END_DECLARE_EVENT_TYPES()

#define wxArrayLengthCtrlHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxArrayLengthCtrlEventFunction, &func)

#define wx__DECLARE_ARRAY_LENGTH_CTRL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_ARRAY_LENGTH_CTRL_ ## evt, id, wxArrayLengthCtrlHandler(fn))	

#define EVT_ARRAY_CTRL_VALUE_CHANGED(id, fn) wx__DECLARE_ARRAY_LENGTH_CTRL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxArrayLengthCtrl : public wxPanel
{
public:
	wxArrayLengthCtrl(wxWindow *parent_, wxWindowID id_,
					  const char *label_,
					  unsigned int value_, 
					  const wxPoint& pos_ = wxDefaultPosition,
					  const wxSize& size_ = wxDefaultSize,
					  long style_ = wxBORDER_NONE);

	void setValue(unsigned int value_);
	unsigned int getValue() const;
protected:
private:
	void fireEvent();
public:
protected:
private:
	void OnTextEntered(wxCommandEvent &evt);
public:
protected:
private:
	unsigned int		value;

	wxStaticText		*staticText;
	wxTextCtrl			*textCtrl;
};
 
#endif