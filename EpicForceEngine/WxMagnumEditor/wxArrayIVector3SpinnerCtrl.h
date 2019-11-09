#ifndef _wxArrayIVector3SpinnerCtrl_h_
#define _wxArrayIVector3SpinnerCtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"
#include "wxIVector3SpinnerCtrl.h"
#include "wxIntSpinnerCtrl.h"
#include "wxArrayLengthCtrl.h"
#include "wxCollapsePanelCtrl.h"
#include "Array.h"
using namespace Magnum;

class wxArrayIVector3SpinnerCtrlEvent : public wxNotifyEvent
{
public:
	wxArrayIVector3SpinnerCtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxArrayIVector3SpinnerCtrlEvent(const wxArrayIVector3SpinnerCtrlEvent& event)
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

	const Vector<IVector3> &GetValue() const 
	{ 
		return values; 
	};

	void SetValue(const Vector<IVector3> &values_) 
	{
		values = values_;
	}

	wxEvent* Clone() const {return new wxArrayIVector3SpinnerCtrlEvent(*this); }
protected:
private:
	wxString name;
	Vector<IVector3> values;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxArrayIVector3SpinnerCtrlEvent)
};

typedef void (wxEvtHandler::*wxArrayIVector3SpinnerCtrlEventFunction)(wxArrayIVector3SpinnerCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_IVECTOR3_SPINNER_CTRL_VALUE_CHANGED , 1 )
END_DECLARE_EVENT_TYPES()

#define wxArrayIVector3SpinnerCtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxArrayIVector3SpinnerCtrlEventFunction, &func)

#define wx__DECLARE_ARRAY_IVECTOR3_SPINNER_CTRL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_ARRAY_IVECTOR3_SPINNER_CTRL_ ## evt, id, wxArrayIVector3SpinnerCtrlEventHandler(fn))	

#define EVT_ARRAY_IVECTOR3_SPINNER_CTRL_VALUE_CHANGED(id, fn)  wx__DECLARE_ARRAY_IVECTOR3_SPINNER_CTRL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxArrayIVector3SpinnerCtrl : public wxCollapsePanelCtrl
{
public:
	wxArrayIVector3SpinnerCtrl(wxWindow *parent_, wxWindowID id_,
						      const char *caption_,
						      const Vector<IVector3> &values_, const IVector3 &minValue_, const IVector3 &maxValue_,
							  wxWindow *topLevelWindow_ = 0,
						      const wxPoint& pos_ = wxDefaultPosition,
						      const wxSize& size_ = wxDefaultSize,
						      long style_ = wxCP_DEFAULT_STYLE);

	void setLength(int length_);
	int getLength() const;

	void setMinValue(const IVector3 &value_);
	IVector3 getMinValue() const;

	void setMaxValue(const IVector3 &value_);
	IVector3 getMaxValue() const;

	void setValue(int idx, const IVector3 &value_);
	IVector3 getValue(int idx) const;
protected:
private:
	void createElementsUI();
	void destroyElementsUI();
	void resizeElementsUI(int newLength);
public:
protected:
private:
	void onLengthChanged(wxArrayLengthCtrlEvent &evt);
	void onIVector3ValueChanged(wxIVector3SpinnerCtrlEvent &evt);
public:
protected:
private:
	Vector<IVector3>				values;
	IVector3						minValue;
	IVector3						maxValue;

	wxBoxSizer						*hBox;
	wxFlexGridSizer					*flexSizer;

	wxArrayLengthCtrl				*numElementsSpinner;
	Vector<wxIVector3SpinnerCtrl *>	vector3Spinners;
};

#endif