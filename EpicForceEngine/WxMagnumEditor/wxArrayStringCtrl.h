#ifndef _wxArrayStringCtrl_h_
#define _wxArrayStringCtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"
#include "wxStringCtrl.h"
#include "wxArrayLengthCtrl.h"
#include "wxCollapsePanelCtrl.h"
#include "Array.h"
using namespace Magnum;

class wxArrayStringCtrlEvent : public wxNotifyEvent
{
public:
	wxArrayStringCtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxArrayStringCtrlEvent(const wxArrayStringCtrlEvent& event)
	: wxNotifyEvent(event)
	, name(event.name)
	, values(event.values)
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

	const Vector<String> &GetValue() const 
	{ 
		return values; 
	};

	void SetValue(const Vector<String> &values_) 
	{
		values = values_;
	}

	wxEvent* Clone() const {return new wxArrayStringCtrlEvent(*this); }
protected:
private:
	wxString name;
	Vector<String> values;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxArrayStringCtrlEvent)
};

typedef void (wxEvtHandler::*wxArrayStringCtrlEventFunction)(wxArrayStringCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_STRING_CTRL_VALUE_CHANGED , 1 )
END_DECLARE_EVENT_TYPES()

#define wxArrayStringCtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxArrayStringCtrlEventFunction, &func)

#define wx__DECLARE_ARRAY_STRING_CTRL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_ARRAY_STRING_CTRL_ ## evt, id, wxArrayStringCtrlEventHandler(fn))

#define EVT_ARRAY_STRING_CTRL_VALUE_CHANGED(id, fn)  wx__DECLARE_ARRAY_STRING_CTRL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxArrayStringCtrl : public wxCollapsePanelCtrl
{
public:
	wxArrayStringCtrl(wxWindow *parent_, wxWindowID id_,
					  const char *label_,
					  const Vector<String> &values_, 
					  wxWindow *topLevelWindow_ = 0,
					  const wxPoint& pos_ = wxDefaultPosition,
					  const wxSize& size_ = wxDefaultSize,
					  long style_ = wxCP_DEFAULT_STYLE);

	void setLength(int length_);
	int getLength() const;

	void setValue(int idx, const String &value_);
	String getValue(int idx) const;
protected:
private:
	void createElementsUI();
	void destroyElementsUI();
	void resizeElementsUI(int newLength);
public:
protected:
private:
	void onLengthChanged(wxArrayLengthCtrlEvent &evt);
	void onStringValueChanged(wxStringCtrlEvent &evt);
public:
protected:
private:
	Vector<String>					values;

	wxBoxSizer						*hBox;
	wxFlexGridSizer					*flexSizer;

	wxArrayLengthCtrl				*numElementsSpinner;
	Vector<wxStringCtrl *>			stringCtrls;
};

#endif