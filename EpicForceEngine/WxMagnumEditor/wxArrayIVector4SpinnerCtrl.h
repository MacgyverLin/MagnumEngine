#ifndef _wxArrayIVector4SpinnerCtrl_h_
#define _wxArrayIVector4SpinnerCtrl_h_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wxdef.h"
#include "wxIVector4SpinnerCtrl.h"
#include "wxIntSpinnerCtrl.h"
#include "wxArrayLengthCtrl.h"
#include "wxCollapsePanelCtrl.h"
#include "Array.h"
using namespace Magnum;

class wxArrayIVector4SpinnerCtrlEvent : public wxNotifyEvent
{
public:
	wxArrayIVector4SpinnerCtrlEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
	: wxNotifyEvent(commandType, winid)
	{
	}

	wxArrayIVector4SpinnerCtrlEvent(const wxArrayIVector4SpinnerCtrlEvent& event)
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

	const Vector<IVector4> &GetValue() const 
	{ 
		return values; 
	};

	void SetValue(const Vector<IVector4> &values_) 
	{
		values = values_;
	}

	wxEvent* Clone() const {return new wxArrayIVector4SpinnerCtrlEvent(*this); }
protected:
private:
	wxString name;
	Vector<IVector4> values;

    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(wxArrayIVector4SpinnerCtrlEvent)
};

typedef void (wxEvtHandler::*wxArrayIVector4SpinnerCtrlEventFunction)(wxArrayIVector4SpinnerCtrlEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE( wxEVT_COMMAND_ARRAY_IVECTOR4_SPINNER_CTRL_VALUE_CHANGED , 1 )
END_DECLARE_EVENT_TYPES()

#define wxArrayIVector4SpinnerCtrlEventHandler(func) \
    (wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(wxArrayIVector4SpinnerCtrlEventFunction, &func)

#define wx__DECLARE_ARRAY_IVECTOR4_SPINNER_CTRL_EVT(evt, id, fn) \
    wx__DECLARE_EVT1(wxEVT_COMMAND_ARRAY_IVECTOR4_SPINNER_CTRL_ ## evt, id, wxArrayIVector4SpinnerCtrlEventHandler(fn))	

#define EVT_ARRAY_IVECTOR4_SPINNER_CTRL_VALUE_CHANGED(id, fn)  wx__DECLARE_ARRAY_IVECTOR4_SPINNER_CTRL_EVT(VALUE_CHANGED, id, fn)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class wxArrayIVector4SpinnerCtrl : public wxCollapsePanelCtrl
{
public:
	wxArrayIVector4SpinnerCtrl(wxWindow *parent_, wxWindowID id_,
						      const char *caption_,
						      const Vector<IVector4> &values_, const IVector4 &minValue_, const IVector4 &maxValue_,
							  wxWindow *topLevelWindow_ = 0,
						      const wxPoint& pos_ = wxDefaultPosition,
						      const wxSize& size_ = wxDefaultSize,
						      long style_ = wxCP_DEFAULT_STYLE);

	void setLength(int length_);
	int getLength() const;

	void setMinValue(const IVector4 &value_);
	IVector4 getMinValue() const;

	void setMaxValue(const IVector4 &value_);
	IVector4 getMaxValue() const;

	void setValue(int idx, const IVector4 &value_);
	IVector4 getValue(int idx) const;
protected:
private:
	void createElementsUI();
	void destroyElementsUI();
	void resizeElementsUI(int newLength);
public:
protected:
private:
	void onLengthChanged(wxArrayLengthCtrlEvent &evt);
	void onIVector4ValueChanged(wxIVector4SpinnerCtrlEvent &evt);
public:
protected:
private:
	Vector<IVector4>				values;
	IVector4						minValue;
	IVector4						maxValue;

	wxBoxSizer						*hBox;
	wxFlexGridSizer					*flexSizer;

	wxArrayLengthCtrl				*numElementsSpinner;
	Vector<wxIVector4SpinnerCtrl *>	vector4Spinners;
};

#endif