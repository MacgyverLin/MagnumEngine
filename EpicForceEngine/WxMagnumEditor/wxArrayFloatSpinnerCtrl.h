#ifndef _wxArrayFloatSpinnerCtrl_h_
#define _wxArrayFloatSpinnerCtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"
#include "wxFloatSpinnerCtrl.h"
#include "wxArrayLengthCtrl.h"
#include "wxCollapsePanelCtrl.h"
#include "Array.h"
using namespace Magnum;

class wxArrayFloatSpinnerCtrlEvent : public wxNotifyEvent
{
public:
	wxArrayFloatSpinnerCtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxArrayFloatSpinnerCtrlEvent(const wxArrayFloatSpinnerCtrlEvent& event)
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

	const Vector<float> &GetValue() const 
	{ 
		return values; 
	};

	void SetValue(const Vector<float> &values_) 
	{
		values = values_;
	}

	wxEvent* Clone() const {return new wxArrayFloatSpinnerCtrlEvent(*this); }
protected:
private:
	wxString name;
	Vector<float> values;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxArrayFloatSpinnerCtrlEvent)
};

typedef void (wxEvtHandler::*wxArrayFloatSpinnerCtrlEventFunction)(wxArrayFloatSpinnerCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_FLOAT_SPINNER_CTRL_VALUE_CHANGED , 1 )
END_DECLARE_EVENT_TYPES()

#define wxArrayFloatSpinnerCtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxArrayFloatSpinnerCtrlEventFunction, &func)

#define wx__DECLARE_ARRAY_FLOAT_SPINNER_CTRL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_ARRAY_FLOAT_SPINNER_CTRL_ ## evt, id, wxArrayFloatSpinnerCtrlEventHandler(fn))

#define EVT_ARRAY_FLOAT_SPINNER_CTRL_VALUE_CHANGED(id, fn)  wx__DECLARE_ARRAY_FLOAT_SPINNER_CTRL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxArrayFloatSpinnerCtrl : public wxCollapsePanelCtrl
{
public:
	wxArrayFloatSpinnerCtrl(wxWindow *parent_, wxWindowID id_,
						    const char *label_,
						    const Vector<float> &values_, float minValue_, float maxValue_,
						    wxWindow *topLevelWindow_ = 0,
						    const wxPoint& pos_ = wxDefaultPosition,
						    const wxSize& size_ = wxDefaultSize,
						    long style_ = wxCP_DEFAULT_STYLE);

	void setLength(int length_);
	int getLength() const;

	void setMinValue(float value_);
	float getMinValue() const;

	void setMaxValue(float value_);
	float getMaxValue() const;

	void setValue(int idx, float value_);
	float getValue(int idx) const;
protected:
private:
	void createElementsUI();
	void destroyElementsUI();
	void resizeElementsUI(int newLength);
public:
protected:
private:
	void onLengthChanged(wxArrayLengthCtrlEvent &evt);
	void onFloatValueChanged(wxFloatSpinnerCtrlEvent &evt);
public:
protected:
private:
	Vector<float >					values;
	float 							minValue;
	float 							maxValue;

	wxBoxSizer						*hBox;
	wxFlexGridSizer					*flexSizer;
	
	wxArrayLengthCtrl				*numElementsSpinner;
	Vector<wxFloatSpinnerCtrl *>	floatSpinners;
};

#endif