#ifndef _wxArrayUIntSpinnerCtrl_h_
#define _wxArrayUIntSpinnerCtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"
#include "wxUIntSpinnerCtrl.h"
#include "wxArrayLengthCtrl.h"
#include "wxCollapsePanelCtrl.h"
#include "Array.h"
using namespace Magnum;

class wxArrayUIntSpinnerCtrlEvent : public wxNotifyEvent
{
public:
	wxArrayUIntSpinnerCtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxArrayUIntSpinnerCtrlEvent(const wxArrayUIntSpinnerCtrlEvent& event)
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

	const Vector<unsigned int> &GetValue() const 
	{ 
		return values; 
	};

	void SetValue(const Vector<unsigned int> &values_) 
	{
		values = values_;
	}

	wxEvent* Clone() const {return new wxArrayUIntSpinnerCtrlEvent(*this); }
protected:
private:
	wxString name;
	Vector<unsigned int> values;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxArrayUIntSpinnerCtrlEvent)
};

typedef void (wxEvtHandler::*wxArrayUIntSpinnerCtrlEventFunction)(wxArrayUIntSpinnerCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_UINT_SPINNER_CTRL_VALUE_CHANGED , 1 )
END_DECLARE_EVENT_TYPES()

#define wxArrayUIntSpinnerCtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxArrayUIntSpinnerCtrlEventFunction, &func)

#define wx__DECLARE_ARRAY_UINT_SPINNER_CTRL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_ARRAY_UINT_SPINNER_CTRL_ ## evt, id, wxArrayUIntSpinnerCtrlEventHandler(fn))

#define EVT_ARRAY_UINT_SPINNER_CTRL_VALUE_CHANGED(id, fn)  wx__DECLARE_ARRAY_UINT_SPINNER_CTRL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxArrayUIntSpinnerCtrl : public wxCollapsePanelCtrl
{
public:
	wxArrayUIntSpinnerCtrl(wxWindow *parent_, wxWindowID id_,
						  const char *label_,
						  const Vector<unsigned int> &values_, unsigned int minValue_, unsigned int maxValue_,
						  wxWindow *topLevelWindow_ = 0,
						  const wxPoint& pos_ = wxDefaultPosition,
						  const wxSize& size_ = wxDefaultSize,
						  long style_ = wxCP_DEFAULT_STYLE);

	void setLength(int length_);
	int getLength() const;

	void setMinValue(unsigned int value_);
	unsigned int getMinValue() const;

	void setMaxValue(unsigned int value_);
	unsigned int getMaxValue() const;

	void setValue(int idx, unsigned int value_);
	unsigned int getValue(int idx) const;
protected:
private:
	void createElementsUI();
	void destroyElementsUI();
	void resizeElementsUI(int newLength);
public:
protected:
private:
	void onLengthChanged(wxArrayLengthCtrlEvent &evt);
	void onUIntValueChanged(wxUIntSpinnerCtrlEvent &evt);
public:
protected:
private:
	Vector<unsigned int>			values;
	unsigned int					minValue;
	unsigned int					maxValue;

	wxBoxSizer						*hBox;
	wxFlexGridSizer					*flexSizer;
	
	wxArrayLengthCtrl				*numElementsSpinner;
	Vector<wxUIntSpinnerCtrl *>		uintSpinners;
};

#endif