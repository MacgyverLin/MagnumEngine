#ifndef _wxArrayDoubleSpinnerCtrl_h_
#define _wxArrayDoubleSpinnerCtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"
#include "wxDoubleSpinnerCtrl.h"
#include "wxIntSpinnerCtrl.h"
#include "wxArrayLengthCtrl.h"
#include "wxCollapsePanelCtrl.h"
#include "Array.h"
using namespace Magnum;

class wxArrayDoubleSpinnerCtrlEvent : public wxNotifyEvent
{
public:
	wxArrayDoubleSpinnerCtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxArrayDoubleSpinnerCtrlEvent(const wxArrayDoubleSpinnerCtrlEvent& event)
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

	const Vector<double> &GetValue() const 
	{ 
		return values; 
	};

	void SetValue(const Vector<double> &values_) 
	{
		values = values_;
	}

	wxEvent* Clone() const {return new wxArrayDoubleSpinnerCtrlEvent(*this); }
protected:
private:
	wxString name;
	Vector<double> values;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxArrayDoubleSpinnerCtrlEvent)
};

typedef void (wxEvtHandler::*wxArrayDoubleSpinnerCtrlEventFunction)(wxArrayDoubleSpinnerCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_DOUBLE_SPINNER_CTRL_VALUE_CHANGED , 1 )
END_DECLARE_EVENT_TYPES()

#define wxArrayDoubleSpinnerCtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxArrayDoubleSpinnerCtrlEventFunction, &func)

#define wx__DECLARE_ARRAY_DOUBLE_SPINNER_CTRL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_ARRAY_DOUBLE_SPINNER_CTRL_ ## evt, id, wxArrayDoubleSpinnerCtrlEventHandler(fn))	

#define EVT_ARRAY_DOUBLE_SPINNER_CTRL_VALUE_CHANGED(id, fn)  wx__DECLARE_ARRAY_DOUBLE_SPINNER_CTRL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxArrayDoubleSpinnerCtrl : public wxCollapsePanelCtrl
{
public:
	wxArrayDoubleSpinnerCtrl(wxWindow *parent_, wxWindowID id_,
						     const char *caption_,
						     const Vector<double> &values_, const double &minValue_, const double &maxValue_,
							 wxWindow *topLevelWindow_ = 0,
						     const wxPoint& pos_ = wxDefaultPosition,
						     const wxSize& size_ = wxDefaultSize,
						     long style_ = wxCP_DEFAULT_STYLE);

	void setLength(int length_);
	int getLength() const;

	void setMinValue(const double &value_);
	double getMinValue() const;

	void setMaxValue(const double &value_);
	double getMaxValue() const;

	void setValue(int idx, const double &value_);
	double getValue(int idx) const;
protected:
private:
	void createElementsUI();
	void destroyElementsUI();
	void resizeElementsUI(int newLength);
public:
protected:
private:
	void onLengthChanged(wxArrayLengthCtrlEvent &evt);
	void onDoubleValueChanged(wxDoubleSpinnerCtrlEvent &evt);
public:
protected:
private:
	Vector<double>					values;
	double							minValue;
	double							maxValue;

	wxBoxSizer						*hBox;
	wxFlexGridSizer					*flexSizer;

	wxArrayLengthCtrl				*numElementsSpinner;
	Vector<wxDoubleSpinnerCtrl *>	doubleSpinners;
};

#endif