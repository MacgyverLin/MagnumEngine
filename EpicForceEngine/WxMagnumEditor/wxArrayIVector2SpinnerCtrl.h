#ifndef _wxArrayIVector2SpinnerCtrl_h_
#define _wxArrayIVector2SpinnerCtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"
#include "wxIVector2SpinnerCtrl.h"
#include "wxIntSpinnerCtrl.h"
#include "wxArrayLengthCtrl.h"
#include "wxCollapsePanelCtrl.h"
#include "Array.h"
using namespace Magnum;

class wxArrayIVector2SpinnerCtrlEvent : public wxNotifyEvent
{
public:
	wxArrayIVector2SpinnerCtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxArrayIVector2SpinnerCtrlEvent(const wxArrayIVector2SpinnerCtrlEvent& event)
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

	const Vector<IVector2> &GetValue() const 
	{ 
		return values; 
	};

	void SetValue(const Vector<IVector2> &values_) 
	{
		values = values_;
	}

	wxEvent* Clone() const {return new wxArrayIVector2SpinnerCtrlEvent(*this); }
protected:
private:
	wxString name;
	Vector<IVector2> values;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxArrayIVector2SpinnerCtrlEvent)
};

typedef void (wxEvtHandler::*wxArrayIVector2SpinnerCtrlEventFunction)(wxArrayIVector2SpinnerCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_IVECTOR2_SPINNER_CTRL_VALUE_CHANGED , 1 )
END_DECLARE_EVENT_TYPES()

#define wxArrayIVector2SpinnerCtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxArrayIVector2SpinnerCtrlEventFunction, &func)

#define wx__DECLARE_ARRAY_IVECTOR2_SPINNER_CTRL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_ARRAY_IVECTOR2_SPINNER_CTRL_ ## evt, id, wxArrayIVector2SpinnerCtrlEventHandler(fn))	

#define EVT_ARRAY_IVECTOR2_SPINNER_CTRL_VALUE_CHANGED(id, fn)  wx__DECLARE_ARRAY_IVECTOR2_SPINNER_CTRL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxArrayIVector2SpinnerCtrl : public wxCollapsePanelCtrl
{
public:
	wxArrayIVector2SpinnerCtrl(wxWindow *parent_, wxWindowID id_,
						      const char *caption_,
						      const Vector<IVector2> &values_, const IVector2 &minValue_, const IVector2 &maxValue_,
							  wxWindow *topLevelWindow_ = 0,
						      const wxPoint& pos_ = wxDefaultPosition,
						      const wxSize& size_ = wxDefaultSize,
						      long style_ = wxCP_DEFAULT_STYLE);

	void setLength(int length_);
	int getLength() const;

	void setMinValue(const IVector2 &value_);
	IVector2 getMinValue() const;

	void setMaxValue(const IVector2 &value_);
	IVector2 getMaxValue() const;

	void setValue(int idx, const IVector2 &value_);
	IVector2 getValue(int idx) const;
protected:
private:
	void createElementsUI();
	void destroyElementsUI();
	void resizeElementsUI(int newLength);
public:
protected:
private:
	void onLengthChanged(wxArrayLengthCtrlEvent &evt);
	void onIVector2ValueChanged(wxIVector2SpinnerCtrlEvent &evt);
public:
protected:
private:
	Vector<IVector2>				values;
	IVector2						minValue;
	IVector2						maxValue;

	wxBoxSizer						*hBox;
	wxFlexGridSizer					*flexSizer;

	wxArrayLengthCtrl				*numElementsSpinner;
	Vector<wxIVector2SpinnerCtrl *>	vector2Spinners;
};

#endif