#ifndef _wxArrayIntSpinnerCtrl_h_
#define _wxArrayIntSpinnerCtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"
#include "wxIntSpinnerCtrl.h"
#include "wxArrayLengthCtrl.h"
#include "wxCollapsePanelCtrl.h"
#include "Array.h"
using namespace Magnum;

class wxArrayIntSpinnerCtrlEvent : public wxNotifyEvent
{
public:
	wxArrayIntSpinnerCtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxArrayIntSpinnerCtrlEvent(const wxArrayIntSpinnerCtrlEvent& event)
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

	const Vector<int> &GetValue() const 
	{ 
		return values; 
	};

	void SetValue(const Vector<int> &values_) 
	{
		values = values_;
	}

	wxEvent* Clone() const {return new wxArrayIntSpinnerCtrlEvent(*this); }
protected:
private:
	wxString name;
	Vector<int> values;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxArrayIntSpinnerCtrlEvent)
};

typedef void (wxEvtHandler::*wxArrayIntSpinnerCtrlEventFunction)(wxArrayIntSpinnerCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_INT_SPINNER_CTRL_VALUE_CHANGED , 1 )
END_DECLARE_EVENT_TYPES()

#define wxArrayIntSpinnerCtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxArrayIntSpinnerCtrlEventFunction, &func)

#define wx__DECLARE_ARRAY_INT_SPINNER_CTRL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_ARRAY_INT_SPINNER_CTRL_ ## evt, id, wxArrayIntSpinnerCtrlEventHandler(fn))

#define EVT_ARRAY_INT_SPINNER_CTRL_VALUE_CHANGED(id, fn)  wx__DECLARE_ARRAY_INT_SPINNER_CTRL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxArrayIntSpinnerCtrl : public wxCollapsePanelCtrl
{
public:
	wxArrayIntSpinnerCtrl(wxWindow *parent_, wxWindowID id_,
						  const char *label_,
						  const Vector<int> &values_, int minValue_, int maxValue_,
						  wxWindow *topLevelWindow_ = 0,
						  const wxPoint& pos_ = wxDefaultPosition,
						  const wxSize& size_ = wxDefaultSize,
						  long style_ = wxCP_DEFAULT_STYLE);

	void setLength(int length_);
	int getLength() const;

	void setMinValue(int value_);
	int getMinValue() const;

	void setMaxValue(int value_);
	int getMaxValue() const;

	void setValue(int idx, int value_);
	int getValue(int idx) const;
protected:
private:
	void createElementsUI();
	void destroyElementsUI();
	void resizeElementsUI(int newLength);
public:
protected:
private:
	void onLengthChanged(wxArrayLengthCtrlEvent &evt);
	void onIntValueChanged(wxIntSpinnerCtrlEvent &evt);
public:
protected:
private:
	Vector<int>						values;
	int								minValue;
	int								maxValue;

	wxBoxSizer						*hBox;
	wxFlexGridSizer					*flexSizer;
	
	wxArrayLengthCtrl				*numElementsSpinner;
	Vector<wxIntSpinnerCtrl *>		intSpinners;
};

#endif