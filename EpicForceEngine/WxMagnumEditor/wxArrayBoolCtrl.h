#ifndef _wxArrayBoolCtrl_h_
#define _wxArrayBoolCtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"
#include "wxBoolCtrl.h"
#include "wxArrayLengthCtrl.h"
#include "wxCollapsePanelCtrl.h"
#include "Array.h"
using namespace Magnum;

class wxArrayBoolCtrlEvent : public wxNotifyEvent
{
public:
	wxArrayBoolCtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxArrayBoolCtrlEvent(const wxArrayBoolCtrlEvent& event)
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

	const Vector<bool> &GetValue() const 
	{ 
		return values; 
	};

	void SetValue(const Vector<bool> &values_) 
	{
		values = values_;
	}

	wxEvent* Clone() const {return new wxArrayBoolCtrlEvent(*this); }
protected:
private:
	wxString name;
	Vector<bool> values;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxArrayBoolCtrlEvent)
};

typedef void (wxEvtHandler::*wxArrayBoolCtrlEventFunction)(wxArrayBoolCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_BOOL_CTRL_VALUE_CHANGED , 1 )
END_DECLARE_EVENT_TYPES()

#define wxArrayBoolCtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxArrayBoolCtrlEventFunction, &func)

#define wx__DECLARE_ARRAY_BOOL_CTRL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_ARRAY_BOOL_CTRL_ ## evt, id, wxArrayBoolCtrlEventHandler(fn))

#define EVT_ARRAY_BOOL_CTRL_VALUE_CHANGED(id, fn)  wx__DECLARE_ARRAY_BOOL_CTRL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxArrayBoolCtrl : public wxCollapsePanelCtrl
{
public:
	wxArrayBoolCtrl(wxWindow *parent_, wxWindowID id_,
					const char *label_,
					const Vector<bool> &values_, 
					wxWindow *topLevelWindow_ = 0,
					const wxPoint& pos_ = wxDefaultPosition,
					const wxSize& size_ = wxDefaultSize,
					long style_ = wxCP_DEFAULT_STYLE);

	void setLength(int length_);
	int getLength() const;

	void setValue(int idx, bool value_);
	bool getValue(int idx) const;
protected:
private:
	void createElementsUI();
	void destroyElementsUI();
	void resizeElementsUI(int newLength);
public:
protected:
private:
	void onLengthChanged(wxArrayLengthCtrlEvent &evt);
	void onBoolValueChanged(wxBoolCtrlEvent &evt);
public:
protected:
private:
	Vector<bool>					values;

	wxBoxSizer						*hBox;
	wxFlexGridSizer					*flexSizer;

	wxArrayLengthCtrl				*numElementsSpinner;
	Vector<wxBoolCtrl *>			boolCtrls;
};

#endif