#ifndef _wxArrayVector3SpinnerCtrl_h_
#define _wxArrayVector3SpinnerCtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"
#include "wxVector3SpinnerCtrl.h"
#include "wxIntSpinnerCtrl.h"
#include "wxArrayLengthCtrl.h"
#include "wxCollapsePanelCtrl.h"
#include "Array.h"
using namespace Magnum;

class wxArrayVector3SpinnerCtrlEvent : public wxNotifyEvent
{
public:
	wxArrayVector3SpinnerCtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxArrayVector3SpinnerCtrlEvent(const wxArrayVector3SpinnerCtrlEvent& event)
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

	const Vector<Vector3> &GetValue() const 
	{ 
		return values; 
	};

	void SetValue(const Vector<Vector3> &values_) 
	{
		values = values_;
	}

	wxEvent* Clone() const {return new wxArrayVector3SpinnerCtrlEvent(*this); }
protected:
private:
	wxString name;
	Vector<Vector3> values;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxArrayVector3SpinnerCtrlEvent)
};

typedef void (wxEvtHandler::*wxArrayVector3SpinnerCtrlEventFunction)(wxArrayVector3SpinnerCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_VECTOR3_SPINNER_CTRL_VALUE_CHANGED , 1 )
END_DECLARE_EVENT_TYPES()

#define wxArrayVector3SpinnerCtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxArrayVector3SpinnerCtrlEventFunction, &func)

#define wx__DECLARE_ARRAY_VECTOR3_SPINNER_CTRL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_ARRAY_VECTOR3_SPINNER_CTRL_ ## evt, id, wxArrayVector3SpinnerCtrlEventHandler(fn))	

#define EVT_ARRAY_VECTOR3_SPINNER_CTRL_VALUE_CHANGED(id, fn)  wx__DECLARE_ARRAY_VECTOR3_SPINNER_CTRL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxArrayVector3SpinnerCtrl : public wxCollapsePanelCtrl
{
public:
	wxArrayVector3SpinnerCtrl(wxWindow *parent_, wxWindowID id_,
						      const char *caption_,
						      const Vector<Vector3> &values_, const Vector3 &minValue_, const Vector3 &maxValue_,
							  wxWindow *topLevelWindow_ = 0,
						      const wxPoint& pos_ = wxDefaultPosition,
						      const wxSize& size_ = wxDefaultSize,
						      long style_ = wxCP_DEFAULT_STYLE);

	void setLength(int length_);
	int getLength() const;

	void setMinValue(const Vector3 &value_);
	Vector3 getMinValue() const;

	void setMaxValue(const Vector3 &value_);
	Vector3 getMaxValue() const;

	void setValue(int idx, const Vector3 &value_);
	Vector3 getValue(int idx) const;
protected:
private:
	void createElementsUI();
	void destroyElementsUI();
	void resizeElementsUI(int newLength);
public:
protected:
private:
	void onLengthChanged(wxArrayLengthCtrlEvent &evt);
	void onVector3ValueChanged(wxVector3SpinnerCtrlEvent &evt);
public:
protected:
private:
	Vector<Vector3>					values;
	Vector3							minValue;
	Vector3							maxValue;

	wxBoxSizer						*hBox;
	wxFlexGridSizer					*flexSizer;

	wxArrayLengthCtrl				*numElementsSpinner;
	Vector<wxVector3SpinnerCtrl *>	vector3Spinners;
};

#endif